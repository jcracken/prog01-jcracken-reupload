#include "ppm.h"

ppm::ppm(){
  this->data = new unsigned char[256];
  this->width = 0;
  this->height = 0;
  this->maxVal = 0;
}

void ppm::readData(std::string name){
  std::ifstream input(name.append(".ppm"), std::ifstream::in);
  input >> this->width;
  input >> this->height;
  input >> this->maxVal;
  input.close();
  std::ifstream input(name.append(".ppm"), std::ios::binary);
  if(input == NULL){
    exit(EXIT_FAILURE);
  }
  input.read(this->data, this->maxVal);
}
unsigned char* ppm::returnData(){
  return this->data;
}
int ppm::returnWidth(){
  return this->width;
}
int ppm::returnHeight(){
  return this->height;
}
int ppm::returnMaxVal(){
  return this->maxVal;
}
