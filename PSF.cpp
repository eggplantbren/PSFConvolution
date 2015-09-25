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

