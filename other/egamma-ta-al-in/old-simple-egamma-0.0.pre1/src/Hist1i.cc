/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
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

/** Set histogram properties.
    \param minimum value
    \param maximum value
    \param quantity of bins.
*/
void Hist1i::set(const double a_min, const double a_max, const int a_bins)
{
  min = a_min;
  max = a_max;
  nbins = a_bins;
  
  if(max<min){max = a_min; min = a_max;}
  
  h = (max-min)/nbins;
  if(hist!=NULL && nbins>0)
    delete hist;
  else
    return;
  
  hist = new int[nbins];
  for (int i=0; i<nbins; i++) hist[i] = 0;
  
}

void Hist1i::clear()
{
  if(hist!=NULL)
    for (int i=0; i<nbins; i++) hist[i] = 0;
}

Hist1i::~Hist1i()
{
  if(hist!=NULL) delete [] hist;
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
    f << bin(i) << "\t" << hist[i] << "\n";
  f.close();
  
  string dat_name = fname;
  dat_name.append(".dat");
  ofstream fdat(dat_name.data());
  for (int i=0; i<nbins; i++)
    if(hist[i]>0)
      fdat << bin(i) << "\t" << hist[i] << "\n";
  fdat.close();
    
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

