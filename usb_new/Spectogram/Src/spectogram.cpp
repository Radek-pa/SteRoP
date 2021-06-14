#include "spectogram.h"

double hanning(int i, int nn) {
	return (0.5 * (1.0 - cos(2.0*M_PI*(double)i / (double)(nn - 1))));
}

int _spectogram()
{
	//const char *path = "C:/Users/ikill/source/repos/fftw/fftw/CantinaBand3.wav";
	int flag_ex = 0;

	int n_frames = 22050;
	uint8_t buff[44];
	uint8_t ptr[22050];
	uint8_t space[] = {","};

	while(flag_ex == 0){
	MX_USB_HOST_Process();
		if(open_to_read() == 1){
			Read_with_open(buff,sizeof(buff));
			//float audio[22050];
			double ptr_double;
			const char* error = NULL;
			int amp;
			real_type sampl[512];
			complex_type freq[512];

				//std::cout << audioFile.samples[0][i] << std::endl;
				//audio[i]=audioFile.samples[0][i]*hanning(i, n_samples)*10;
			Read_with_open(ptr, sizeof(ptr));
				//audio[i] = ptr;
				//std::cout << audio_2[i] << std::endl;
			Close_usb();

			open_to_write("Fequenc.txt");
			for (int i = 0; i < 43 ; ++i){
				for(int j = 0; j < 512 ; ++j){
					sampl[j] = ptr[i*512+j];
				}
				simple_fft::FFT(sampl,freq,512,error);
				for(int j = 0; j < 1024 ; ++j){
					ptr_double = abs(freq[j]);
					amp = ptr_double/2000000;
					Write_with_open((uint8_t*)&amp,sizeof(amp));
					Write_with_open(space,sizeof(space));
				}
			}
			//gaborator::parameters params(48, 20.0 / fs, 440.0 / fs);
			//gaborator::analyzer<float> analyzer(params);
			/*
			gaborator::coefs<float> coefs(analyzer);
			analyzer.analyze(audio, 0, n_frames, coefs);

			int64_t x_origin = 0;
			int64_t y_origin = analyzer.bandpass_bands_begin();

			int x_scale_exp = 10;

			while ((n_frames >> x_scale_exp) > 1000)
				x_scale_exp++;

			int y_scale_exp = 0;

			int64_t ptr2 = 0;
			int64_t x0 = 0;
			int64_t y0 = 0;
			int64_t x1 = n_frames >> x_scale_exp;
			int64_t y1 = (analyzer.bandpass_bands_end() - analyzer.bandpass_bands_begin()) >> y_scale_exp;
			unsigned int ptr_int = 0;

			std::vector<float> amplitudes((x1 - x0) * (y1 - y0));
			gaborator::render_p2scale(
					analyzer,
					coefs,
					x_origin, y_origin,
					x0, x1, x_scale_exp,
					y0, y1, y_scale_exp,
					amplitudes.data());

			float gain = 10;
			uint8_t buf1[] = {"P5\n"};
			uint8_t buf2[] = {"\n255\n"};
			uint8_t buf3[] = {" "};
			ptr2 = x1-x0;
			open_to_write("image.pgm");
			Write_with_open(buf1, sizeof(buf1));
			Write_with_open((uint8_t*)&ptr2, sizeof(ptr2));
			Write_with_open(buf3, sizeof(buf3));
			ptr2 = y1-y0;
			Write_with_open((uint8_t*)&ptr2, sizeof(ptr2));
			Write_with_open(buf2, sizeof(buf2));
			for (size_t i = 0; i < amplitudes.size(); i++) {
				ptr_int = gaborator::float2pixel_8bit(amplitudes[i] * gain);
				Write_with_open((uint8_t*)&ptr_int,sizeof(ptr_int));
			}
			*/
			Close_usb();
			flag_ex = 1;
		}
	}
	return 0;
}

