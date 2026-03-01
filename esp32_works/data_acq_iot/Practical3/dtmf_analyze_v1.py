import sounddevice as sd
import numpy as np
from scipy.signal import find_peaks

def record_audio(duration=5, sample_rate=44100):
        # Record audio from the microphone
        audio_data = sd.rec(int(sample_rate * duration), samplerate=sample_rate, channels=1, dtype='float32')
        sd.wait()

        return audio_data.flatten(), sample_rate

def find_dtmf_tones(audio_data, sample_rate):
        # Perform FFT
        spectrum = np.fft.fft(audio_data)
        freqs = np.fft.fftfreq(len(audio_data), 1/sample_rate)

        # Find peaks in the magnitude spectrum
        magnitude_spectrum = np.abs(spectrum)
        peaks, _ = find_peaks(magnitude_spectrum, height=1000)  # Adjust the threshold as needed

        # Design DTMF filters for digits 1 to 5 only
        dtmf_frequencies = {'1': (697, 1209), '2': (697, 1336), '3': (697, 1477), '4': (770, 1209), '5': (770, 1336), '6': (770, 1477), '7': (852, 1209), '8': (852, 1336), '9': (852, 1477), '0': (941, 1336)}
        detected_tones = []

        # Check which combination of row and column frequencies minimizes the overall distance
        for digit, frequencies in dtmf_frequencies.items():
            row_freq, col_freq = frequencies
            for row_peak_index in peaks:
                row_peak_freq = freqs[row_peak_index]
                for col_peak_index in peaks:
                    col_peak_freq = freqs[col_peak_index]

                    # Calculate distances to row and column frequencies
                    row_distance = abs(row_peak_freq - row_freq)
                    col_distance = abs(col_peak_freq - col_freq)

                    # Calculate overall distance
                    total_distance = row_distance + col_distance

                    # Check if the overall distance is below a threshold
                    if total_distance < 50:
                        detected_tones.append(digit)

        return detected_tones

if __name__ == "__main__":
        # Record audio from the microphone
        audio_data, sample_rate = record_audio()

        # Find and display the detected DTMF tones using FFT
        detected_tones = find_dtmf_tones(audio_data, sample_rate)

        if detected_tones:
            print(f"Detected DTMF Tones: {' '.join(detected_tones)}")
        else:
            print("No DTMF tones detected.")
