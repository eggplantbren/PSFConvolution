#include "PSF.h"
#include <fstream>
#include <iostream>

using namespace std;

PSF::PSF(int M, int N)
:M(M), N(N)
,pixels(M, vector<double>(N))
{

}

void PSF::normalise()
{
	double tot = 0.;
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			tot += pixels[i][j];

	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
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
	if(static_cast<int>(everything.size()) != M*N)
	{
		cerr<<"# Error: wrong number of elements in file ";
		cerr<<filename<<"."<<endl;
		cerr<<"# Expected "<<(M*N)<<", found "<<everything.size()<<"."<<endl;
		return;
	}
}

