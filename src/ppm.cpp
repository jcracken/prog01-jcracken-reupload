#include "ppm.h"

ppm::ppm(){
  data = new unsigned char[256];
  width = 0;
  height = 0;
  maxVal = 0;
}

void readData(std::string name){
  std::ifstream input(name.append(".ppm"), std::ifstream::in);
  input >> width;
  input >> height;
  input >> maxVal;
  input.close();
  std::ifstream input(name.append(".ppm"), std::ios::binary);
  if(input == NULL){
    exit(EXIT_FAILURE);
  }
  input.read(data, maxVal);
}
unsigned char* returnData(){
  return data;
}
int returnWidth(){
  return width;
}
int returnHeight(){
  return height;
}
int returnMaxVal(){
  return maxVal;
}
