#ifndef PSFConvolution_PSF_h
#define PSFConvolution_PSF_h

#include <vector>

class PSF
{
	private:
		// Size of the PSF
		int M, N;
		std::vector< std::vector<double> > pixels;

	public:
		// Constructor inputs specify the size of the
		// psf in pixels (vertical then horizontal)
		PSF(int M, int N);
};

#endif

