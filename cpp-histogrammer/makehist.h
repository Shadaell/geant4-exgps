#ifndef MAKEHIST_H
#define MAKEHIST_H

#include <string>
/** 
    Makes a histogramm from input file with floating point values.
    Min/max of the histogramm will be automatically determined.
    \param number of bins of histogramm.
    \param input file name.
    \param output file name.
    
 **/
int make_histogramm(const size_t N_bins, const std::string inputname, const std::string outputname);


#endif
