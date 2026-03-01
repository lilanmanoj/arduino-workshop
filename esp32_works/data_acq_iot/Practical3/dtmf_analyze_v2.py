import sounddevice as sd
import numpy as np
from scipy.signal import find_peaks

def record_audio(duration=5, sample_rate=44100):
        # Record audio from the microphone
        audio_data = sd.rec(int(sample_rate * duration), samplerate=sample_rate, channels=1, dtype='float32')
        sd.wait()

        return audio_data.flatten(), sample_rate

def find_dtmf_tones(audio_data, sample_rate):
    window_duration = 0.1  # 100 ms window
    window_size = int(sample_rate * window_duration)

    dtmf_frequencies = {
        '1': (697, 1209), '2': (697, 1336), '3': (697, 1477),
        '4': (770, 1209), '5': (770, 1336), '6': (770, 1477),
        '7': (852, 1209), '8': (852, 1336), '9': (852, 1477),
        '0': (941, 1336)
    }

    detected_sequence = []
    previous_digit = None

    # Process signal in windows
    for start in range(0, len(audio_data), window_size):
        segment = audio_data[start:start+window_size]

        if len(segment) < window_size:
            break

        spectrum = np.fft.fft(segment)
        freqs = np.fft.fftfreq(len(segment), 1/sample_rate)
        magnitude = np.abs(spectrum)
        detected_digit = None

        for digit, (row_freq, col_freq) in dtmf_frequencies.items():
            # Find closest frequency bins
            row_index = np.argmin(np.abs(freqs - row_freq))
            col_index = np.argmin(np.abs(freqs - col_freq))

            row_magnitude = magnitude[row_index]
            col_magnitude = magnitude[col_index]

            # Threshold check
            if row_magnitude > 100 and col_magnitude > 100:
                detected_digit = digit
                break

        # Append only if digit changes
        if detected_digit and detected_digit != previous_digit:
            detected_sequence.append(detected_digit)
            previous_digit = detected_digit

        # Reset when silence detected
        if detected_digit is None:
            previous_digit = None

    return detected_sequence

if __name__ == "__main__":
        # Record audio from the microphone
        audio_data, sample_rate = record_audio()

        # Find and display the detected DTMF tones using FFT
        detected_tones = find_dtmf_tones(audio_data, sample_rate)

        if detected_tones:
            print(f"Detected DTMF Tones: {' '.join(detected_tones)}")
        else:
            print("No DTMF tones detected.")
