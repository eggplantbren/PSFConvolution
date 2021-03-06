#ifndef PSFConvolution_PSF_h
#define PSFConvolution_PSF_h

#include <vector>
#include <fftw3.h>

class PSF
{
	private:
		// Size of the PSF (in square format)
		int size;
		std::vector< std::vector<double> > pixels;

		// Resized to the size of an image, and
		// 'fftshifted' to fill the corners
		std::vector< std::vector<double> > shifted;

		// The FFT of 'shifted'
		fftw_complex* fft;

		// Do the fft
		void calculate_fft();

		// Useful mod function
		static int mod(int y, int x);

	public:
		// Constructor inputs specify the size of the
		// psf in pixels
		PSF(int size);

		// Copy constructor and operator=
		PSF(const PSF& other);
		void operator = (const PSF& other);

		// Load from file (in centered format)
		void load(const char* filename);

		// Normalise so that the sum is 1
		void normalise();

		// Calculate the 'shifted' version of the PSF
		// with shape MxN
		void calculate_shifted(int M, int N);

		// Getter
		const std::vector< std::vector<double> >& get_shifted() const
		{ return shifted; }
};

#endif

