#include "makehist.h"
#include "xydata_template.h"
#include <iostream>

int make_histogramm(const size_t N_bins, const std::string inputname, const std::string outputname)
{
  if(N_bins == 0 && inputname.empty()) return -1;
  std::ifstream input;
  input.open(inputname.c_str(), std::ios::in );
  float min = 0;
  float max = 0;
  float value;
  input >> value;
  min = max = value;
  size_t cnt_read = 0;
  while(input.good() && !input.eof())
    {
      input >> value;
      min = (value < min)? value : min;
      max = (value > max)? value : max;
      cnt_read++;
    }
  input.close();
  std::cout << "making histogramm with " << N_bins <<" bins...\n";
  std::cout << cnt_read << "\tfloat values had been read.\n";
  std::cout << "min value: " << min
	    << "\tmax value: " << max << "\n";
  if(max <= min)
    {
      std::cout << "(error) wrong max/min values, quitting.\n";
      return -1;
    }
  xydata<float> data;
  data.resize(N_bins);
  double step = (max - min)/N_bins;
  size_t cnt = 0;
  while(cnt < N_bins)
    {
      data.setx(cnt, (cnt + 1)*step);
      cnt++;
    }
  
  input.open(inputname.c_str(), std::ios::in );
  while(input.good() && !input.eof())
    {
      input >> value;
      size_t index = (size_t)(value/step);
      bool ok = false;
      data.sety(index, data.y(index, ok) + 1.0);
    }
  input.close();
  data.write_file(outputname);
  std::cout << "success.\n";
  data.clear();
  return 0;
}
