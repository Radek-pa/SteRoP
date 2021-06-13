#include "spectogram.h"

double hanning(int i, int nn) {
	return (0.5 * (1.0 - cos(2.0*M_PI*(double)i / (double)(nn - 1))));
}

int _spectogram()
{
	//const char *path = "C:/Users/ikill/source/repos/fftw/fftw/CantinaBand3.wav";
	int flag_ex = 0;

	double fs = 8;
	int n_frames = 66150;
	uint8_t buff[44];
	uint8_t ptr;


	while(flag_ex = 0){
	MX_USB_HOST_Process();
		if(open_to_read() == 1){
			Read_with_open(buff, 44);
			std::vector<float> audio(n_frames);
			for (int i = 0; i < n_frames; i++)
			{
				//std::cout << audioFile.samples[0][i] << std::endl;
				//audio[i]=audioFile.samples[0][i]*hanning(i, n_samples)*10;
				Read_with_open(&ptr, 1);
				audio[i] = ptr;
				//std::cout << audio_2[i] << std::endl;
			}

			gaborator::parameters params(48, 20.0 / fs, 440.0 / fs);
			gaborator::analyzer<float> analyzer(params);
			gaborator::coefs<float> coefs(analyzer);
			analyzer.analyze(audio.data(), 0, audio.size(), coefs);

			int64_t x_origin = 0;
			int64_t y_origin = analyzer.bandpass_bands_begin();

			int x_scale_exp = 10;

			while ((n_frames >> x_scale_exp) > 1000)
				x_scale_exp++;

			int y_scale_exp = 0;

			int64_t x0 = 0;
			int64_t y0 = 0;
			int64_t x1 = n_frames >> x_scale_exp;
			int64_t y1 = (analyzer.bandpass_bands_end() - analyzer.bandpass_bands_begin()) >> y_scale_exp;

			std::vector<float> amplitudes((x1 - x0) * (y1 - y0));
			gaborator::render_p2scale(
					analyzer,
					coefs,
					x_origin, y_origin,
					x0, x1, x_scale_exp,
					y0, y1, y_scale_exp,
					amplitudes.data());

			float gain = 10;
			/*
			std::ofstream f;
			f.open("image.pgm", std::ios::out | std::ios::binary);
			f << "P5\n" << (x1 - x0) << ' ' << (y1 - y0) << "\n255\n";
			for (size_t i = 0; i < amplitudes.size(); i++) {
				f.put(gaborator::float2pixel_8bit(amplitudes[i] * gain));
			}
			f.close();
			*/
			Close_usb();
			flag_ex = 1;
		}
	}
	return 0;
}

