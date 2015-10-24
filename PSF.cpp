#include "PSF.h"
#include <fstream>
#include <iostream>

using namespace std;

PSF::PSF(int size)
:size(size)
,pixels(size, vector<double>(size))
{

}

void PSF::normalise()
{
	double tot = 0.;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			tot += pixels[i][j];

	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			pixels[i][j] /= tot;
}

void PSF::load(const char* filename)
{
	// Open the file
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# Error: could not open file "<<filename<<"."<<endl;
		return;
	}

	// Read everything
	double temp;
	vector<double> everything;
	while(fin>>temp)
		everything.push_back(temp);

	// Check the number of values read in vs the supposed size of this
	// PSF
	if(static_cast<int>(everything.size()) != size*size)
	{
		cerr<<"# Error: wrong number of elements in file ";
		cerr<<filename<<"."<<endl;
		cerr<<"# Expected "<<size<<", found "<<everything.size()<<"."<<endl;
		return;
	}

	int k = 0;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			pixels[i][j] = everything[k++];	
	normalise();
}

void PSF::calculate_shifted(int M, int N)
{
	// Resize 'shifted' to be M x N
	shifted.assign(M, vector<double>(N, 0.));

	// Indices within shifted
	int m, n;
	for(int i=0; i<size; i++)
	{
		m = mod(i - size/2, M);
		for(int j=0; j<size; j++)
		{
			n = mod(j - size/2, N);
			shifted[m][n] = pixels[i][j];
		}
	}
}

void PSF::calculate_fft()
{
	// Put shifted into a 1-D array
	double* in = new double[shifted.size()*shifted[0].size()];
	int k = 0;
	for(size_t i=0; i<shifted.size(); i++)
		for(size_t j=0; j<shifted[i].size(); j++)
			in[k++] = shifted[i][j];

	// Make a plan
	fftw_plan plan = fftw_plan_dft_r2c_2d(shifted.size(), shifted[0].size(),
											in, fft, FFTW_MEASURE);
	fftw_execute(plan);

	delete[] in;
}

int PSF::mod(int y, int x)
{
	if(x <= 0)
		cerr<<"# Warning in PSF::mod(int, int)"<<endl;
	if(y >= 0)
		return y - (y/x)*x;
	else
		return (x-1) - mod(-y-1, x);
}

