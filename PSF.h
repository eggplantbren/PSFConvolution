#ifndef PSFConvolution_PSF_h
#define PSFConvolution_PSF_h

#include <vector>

class PSF
{
	private:
		// Size of the PSF (in square format)
		int size;
		std::vector< std::vector<double> > pixels;

	public:
		// Constructor inputs specify the size of the
		// psf in pixels
		PSF(int size);

		// Load from file (in centered format)
		void load(const char* filename);

		// Normalise so that the sum is 1
		void normalise();
};

#endif

