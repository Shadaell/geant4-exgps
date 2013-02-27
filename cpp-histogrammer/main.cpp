#include <iostream>
#include "makehist.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
  std::cout << "USAGE: \n" 
	    << argv[0] << " in_filename out_filename N_BINS\n"
	    << "for example: "
	    << argv[0] << " file1.dat file1_histo.dat 2000\n";
  if( argc < 2)
    {
      //не задано вхідний файл:
      std::cout << "No input file given!\n";
      return -1;
    }
  int ret = -1;
  std::string name1 = argv[1];
  std::string name2 = "output.hist.dat";
  if(argc == 2)
    ret = make_histogramm(2000, name1, name2);

  if(argc > 2)
    name2 = argv[2];
  if(argc == 3)
    ret = make_histogramm(2000, name1, name2);
  if(argc == 4)
    ret = make_histogramm(atol(argv[3]), name1, name2);
  return ret;
}

