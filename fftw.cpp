#include <fftw3.h>
#include "test1.h"
#include <iostream>
#include <stdlib.h>

# define M_PI 3.141592653589793238462643383279502884


// convenience macros for the real and imaginary parts
constexpr int REAL = 0;
constexpr int IMAG = 1;

/* Computes the 1-D fast Fourier transform. */
void fft(fftw_complex* in, fftw_complex* out, int N)
{
	// create a DFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

/* Computes the 1-D inverse fast Fourier transform. */
void ifft(fftw_complex* in, fftw_complex* out, int N)
{
	// create an IDFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
	// scale the output to obtain the exact inverse
	for (int i = 0; i < N; ++i) {
		out[i][REAL] /= N;
		out[i][IMAG] /= N;
	}
}

/* Displays complex numbers in the form a +/- bi. */
void displayComplex(fftw_complex* y, int N)
{
	for (int i = 0; i < N; ++i) {
		if (y[i][IMAG] < 0) {
			std::cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << std::endl;
		}
		else {
			std::cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << std::endl;
		}
	}
}

/* Displays the real parts of complex numbers. */
void displayReal(fftw_complex* y, int N)
{
	for (int i = 0; i < N; ++i) {
		std::cout << y[i][REAL] << std::endl;
	}
}

/* Hanning window. */
double hanning(int i, int nn){
	return (0.5 * (1.0 - cos(2.0*M_PI*(double)i / (double)(nn - 1))));
}

double windowing(int n, double *data, double scale, int i){
	//for (int i = 0; i < n; i++)
	double out;
	out = data[i] *hanning(i, n) / scale;
	return out;
}

void HC_to_polar(long len, const fftw_complex * freq, int conj, double * amp, double * phs){
	int i;
	double rl, im;

	phs[0] = 0.0;
	amp[0] = sqrt((freq[0][REAL]+freq[0][IMAG]) * (freq[0][REAL] + freq[0][IMAG]));
	for (i = 1; i < (len + 1) / 2; i++){
		rl = freq[i][REAL];
		im = freq[len - i][IMAG];
		amp[i] = sqrt(rl * rl + im * im);
		if (amp[i] > 0.0){
			if (conj == 0) phs[i] = atan2(+im, rl);
			else           phs[i] = atan2(-im, rl);
		}
		else
			phs[i] = 0.0;
	}
	if (len % 2 == 0){
		phs[len / 2] = 0.0;
		amp[len / 2] = sqrt((freq[len / 2][REAL] + freq[len / 2][IMAG]) * (freq[len / 2][REAL] + freq[len / 2][IMAG]));
		//amp[len / 2] = sqrt(freq[len / 2] * freq[len / 2]);
	}
}

void HC_to_amp2(int len, const fftw_complex * freq, double scale,double * amp2){
	int i;
	double rl, im;

	amp2[0] = (freq[0][REAL] + freq[0][IMAG]) * (freq[0][REAL] + freq[0][IMAG]) / scale;
	for (i = 1; i < (len + 1) / 2; i++){
		rl = freq[i][REAL];
		im = freq[len - i][IMAG];
		amp2[i] = (rl * rl + im * im) / scale;
	}
	if (len % 2 == 0){
		amp2[len / 2] = (freq[len / 2][REAL] + freq[len / 2][IMAG]) * (freq[len / 2][REAL] + freq[len / 2][IMAG]) / scale;
		//amp2[len / 2] = freq[len / 2] * freq[len / 2] / scale;
	}
}
int main()
{
	AudioFile<double> audioFile;
	audioFile.load("C:/Users/ikill/source/repos/fftw/fftw/CantinaBand3.wav");
	//audioFile.load("C:/Users/ikill/source/repos/fftw/fftw/audiocheck.net_sin_1000Hz_-3dBFS_3s.wav");
	int N = audioFile.getNumSamplesPerChannel();
	int sampleRate = audioFile.getSampleRate();
	int channel = 0;
	int temp;

	int transform_size = 1024;
	int step_size = transform_size / 2;
	int half = transform_size / 2;
	int frames = N / step_size;

	fftw_complex *out;
	fftw_plan p;

	double *processed = new double(transform_size/2+1);
	double *in = new double(transform_size);
	int** result = new int*[frames];
	for (int i = 0; i < frames; i++)
		result[i] = new int[half];
	audioFile.printSummary();

	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * transform_size);

	std::cout << sampleRate << std::endl;

	//Getting data from file in frames
	for (int j = 0; j < frames; j++){
		for (int i = 0; i < step_size; i++){
			in[i] = (double)audioFile.samples[channel][i + step_size * j];
			in[i] = windowing(transform_size, in, 1.0, i);
		}
		
		//Executing fft
		p = fftw_plan_dft_r2c_1d(transform_size, in, out, FFTW_ESTIMATE);
		fftw_execute(p);
		
		//Processing results and normalization for spectrum
		for (int i = 0; i < half; i++) {

			out[i][0] *= (2. / transform_size);                           // real values
			out[i][1] *= (2. / transform_size);                           // complex values
			processed[i] = out[i][0] * out[i][0] + out[i][1] * out[i][1]; // power spectrum
			processed[i] = 10. / log(10.) * log(processed[i] + 1e-6);     // dB

			if (processed[i] <= 0) {
				processed[i] = 0;
			}
			else {
				processed[i] /= 96.;             
				if (processed[i] > 1)
					processed[i] = 1;
			}

			result[j][(half - 1) - i] = processed[i] * 255;
		}
		fftw_destroy_plan(p);
		fftw_cleanup();
	}
	FILE *image;
	image = fopen("image.ppm", "wb");
	fprintf(image, "P2\n");
	fprintf(image, "%d %d\n", frames, half);
	fprintf(image, "255\n");

	for (int i = 0; i < frames; i++) {
		for (int j = 0; j < half; j++) {
			temp = result[i][j];
			fprintf(image, "%d ", temp);
		}
		fprintf(image, "\n");
	}
	fclose(image);
	fftw_free(out);

	return 0;
}