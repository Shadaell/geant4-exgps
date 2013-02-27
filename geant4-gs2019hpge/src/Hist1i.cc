/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
/* ========================================================== */

#include "Hist1i.h"
#include <fstream>
#include <cmath>
using namespace std;

Hist1i::Hist1i(double mi, double ma, int n)
: min(mi), max(ma), nbins(n)
{
  h = (max-min)/nbins;
  hist = new int[nbins];
  for (int i=0; i<nbins; i++) hist[i] = 0;
}

Hist1i::~Hist1i()
{
  delete [] hist;
}

void Hist1i::fill(double x)
{
  if ((min<=x)&&(x<=max)) {
    int i = int((x - min)/h);
    hist[i]++;
  }
}

void Hist1i::save(string fname, string banner)
{
  ofstream f(fname.data());
  f << banner << "\n";
  for (int i=0; i<nbins; i++)
    f << bin(i) << ", " << hist[i] << "\n";
  f.close();
}

void Hist1i::statistics(double& mean, double& rms)
{
  double N = 0.;
	double Sx = 0.;
	double Sx2 = 0.;
	for (int i=0; i<nbins; i++) {
	  N   += hist[i];
	  Sx  += hist[i]*bin(i);
    Sx2 += hist[i]*bin(i)*bin(i);
  }
	
	mean = Sx/N;
	rms = sqrt(Sx2/N - mean*mean);
}

double Hist1i::bin(int i)
{
  return min + (i + .5)*h;
}

