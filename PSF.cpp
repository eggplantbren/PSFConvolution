#include "PSF.h"

using namespace std;

PSF::PSF(int M, int N)
:M(M), N(N)
,pixels(M, vector<double>(N))
{

}

