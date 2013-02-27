/* ========================================================== */
// Code was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
//
// And rewritten by Bogdan Maslovskiy,
// Taras Schevchenko National University of Kyiv, 2011.
/* ========================================================== */

#ifndef Hist1i_H
#define Hist1i_H 1

#include <string>

class Hist1i
{
  public:
    Hist1i(double, double, int);
    ~Hist1i();
    
    void fill(double);
    void save(std::string, std::string);
    void statistics(double& mean, double& rms);
    
    /** Set histogram properties.
	\param minimum value
	\param maximum value
	\param quantity of bins.
     */
    void set(const double a_min, const double a_max, const int a_bins);
    
    void clear();
    
  private:
    inline double bin(int);
    double min, max, h;
    int nbins;
    int* hist;
};

#endif

