/* ========================================================== */
// Labs was written by Anton Korneev and Mechinsky Vitaly, 
// Institute of Nuclear Problems, Belarus, Minsk, September 2007
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
		
  private:
    inline double bin(int);
		double min, max, h;
    int nbins;
    int* hist;
};

#endif

