/* Edge Impulse ingestion SDK */

#define EIDSP_QUANTIZE_FILTERBANK   0

#include <PDM.h>
#include <a24sea052-project-1_inferencing.h>

#define LED_PIN LED_BUILTIN

typedef struct {
    int16_t *buffer;
    uint8_t buf_ready;
    uint32_t buf_count;
    uint32_t n_samples;
} inference_t;

static inference_t inference;
static signed short sampleBuffer[2048];
static bool debug_nn = false;

/* Setup ---------------------------------------------------------------- */
void setup()
{
    Serial.begin(115200);
    while (!Serial);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Edge Impulse Voice Control Demo");

    ei_printf("Inferencing settings:\n");
    ei_printf("\tInterval: %.2f ms\n", (float)EI_CLASSIFIER_INTERVAL_MS);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tSample length: %d ms\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
    ei_printf("\tNo. of classes: %d\n",
        sizeof(ei_classifier_inferencing_categories) /
        sizeof(ei_classifier_inferencing_categories[0]));

    if (!microphone_inference_start(EI_CLASSIFIER_RAW_SAMPLE_COUNT)) {
        ei_printf("ERR: Could not allocate audio buffer\n");
        return;
    }
}

/* Main Loop ------------------------------------------------------------- */
void loop()
{
    Serial.println("Waiting before next recording...");

    // 5 second wait with countdown
    for (int i = 5; i > 0; i--) {
        Serial.print("Waiting ");
        Serial.print(i);
        Serial.println(" seconds...");
        delay(1000);
    }

    // Recording countdown
    Serial.println("Get ready...");
    Serial.println("3");
    delay(1000);
    Serial.println("2");
    delay(1000);
    Serial.println("1");
    delay(1000);

    Serial.println("Recording...");

    if (!microphone_inference_record()) {
        Serial.println("ERR: Failed to record audio");
        return;
    }

    Serial.println("Recording done");

    signal_t signal;
    signal.total_length = EI_CLASSIFIER_RAW_SAMPLE_COUNT;
    signal.get_data = &microphone_audio_signal_get_data;

    ei_impulse_result_t result = { 0 };

    EI_IMPULSE_ERROR r = run_classifier(&signal, &result, debug_nn);
    if (r != EI_IMPULSE_OK) {
        Serial.println("ERR: Failed to run classifier");
        return;
    }

    float on_value = 0;
    float off_value = 0;

    Serial.println("Predictions:");

    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {

        Serial.print("  ");
        Serial.print(result.classification[ix].label);
        Serial.print(": ");
        Serial.println(result.classification[ix].value, 5);

        if (strcmp(result.classification[ix].label, "ON") == 0) {
            on_value = result.classification[ix].value;
        }

        if (strcmp(result.classification[ix].label, "OFF") == 0) {
            off_value = result.classification[ix].value;
        }
    }

    // LED control logic
    if (on_value > 0.7) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
    }
    else if (off_value > 0.7) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
    Serial.print("Anomaly score: ");
    Serial.println(result.anomaly, 3);
#endif

    Serial.println("----------------------------------");
}

/* PDM Callback ---------------------------------------------------------- */
static void pdm_data_ready_inference_callback(void)
{
    int bytesAvailable = PDM.available();
    int bytesRead = PDM.read((char *)&sampleBuffer[0], bytesAvailable);

    if (inference.buf_ready == 0) {
        for (int i = 0; i < bytesRead >> 1; i++) {
            inference.buffer[inference.buf_count++] = sampleBuffer[i];

            if (inference.buf_count >= inference.n_samples) {
                inference.buf_count = 0;
                inference.buf_ready = 1;
                break;
            }
        }
    }
}

/* Start Microphone ------------------------------------------------------ */
static bool microphone_inference_start(uint32_t n_samples)
{
    inference.buffer = (int16_t *)malloc(n_samples * sizeof(int16_t));

    if (inference.buffer == NULL) {
        return false;
    }

    inference.buf_count = 0;
    inference.n_samples = n_samples;
    inference.buf_ready = 0;

    PDM.onReceive(&pdm_data_ready_inference_callback);
    PDM.setBufferSize(4096);

    if (!PDM.begin(1, EI_CLASSIFIER_FREQUENCY)) {
        ei_printf("Failed to start PDM\n");
        microphone_inference_end();
        return false;
    }

    PDM.setGain(80);

    return true;
}

/* Record Audio ---------------------------------------------------------- */
static bool microphone_inference_record(void)
{
    inference.buf_ready = 0;
    inference.buf_count = 0;

    while (inference.buf_ready == 0) {
        delay(10);
    }

    return true;
}

/* Convert Audio --------------------------------------------------------- */
static int microphone_audio_signal_get_data(
    size_t offset,
    size_t length,
    float *out_ptr)
{
    numpy::int16_to_float(&inference.buffer[offset], out_ptr, length);
    return 0;
}

/* End Microphone -------------------------------------------------------- */
static void microphone_inference_end(void)
{
    PDM.end();
    free(inference.buffer);
}

#if !defined(EI_CLASSIFIER_SENSOR) || \
    EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
#error "Invalid model for current sensor."
#endif