#include "PSF.h"
#include <iostream>

using namespace std;

int main()
{
	PSF psf(3);
	psf.load("psf.txt");
	psf.calculate_shifted(10, 10);

	const vector< vector<double> >& shifted = psf.get_shifted();
	for(size_t i=0; i<shifted.size(); i++)
	{
		for(size_t j=0; j<shifted[i].size(); j++)
			cout<<shifted[i][j]<<' ';
		cout<<endl;
	}

	return 0;
}

