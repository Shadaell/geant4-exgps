// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
///*
// Part of simulation for use with GEANT4 code.
// Author  Bogdan Maslovskiy <blinkofnight(at,doggy,removeme)gmail(dot)>,
// Taras Schevchenko National University of Kyiv 2011
//****************

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
  // ofstream f(fname.data());
  // f << banner << "\n";
  // for (int i=0; i<nbins; i++)
  //   f << bin(i) << "\t" << hist[i] << "\n";
  // f.close();
  
  string dat_name = fname;
  dat_name.append(".dat");
  ofstream fdat;
  fdat.open(dat_name.c_str(), std::iostream::out);
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

