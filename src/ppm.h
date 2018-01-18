#ifndef PPM_H
#define PPM_H

#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>

class ppm {
  private:
    char* data;
    int width;
    int height;
    int maxVal;
  public:
    ppm();
    void readData(std::string name);
    char* returnData();
    int returnWidth();
    int returnHeight();
    int returnMaxVal();
};
#endif
