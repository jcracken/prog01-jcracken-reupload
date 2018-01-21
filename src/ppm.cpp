#include "ppm.h"

ppm::ppm(){
  this->data = new char[256];
  this->width = 0;
  this->height = 0;
  this->maxVal = 0;
}

void ppm::readData(std::string name){
  std::ifstream input(name.append(".ppm"), std::ifstream::in);
  std::string temp;
  if(!(input.is_open())){
    exit(EXIT_FAILURE);
  }
  getline(input, temp);
  if(temp.compare("P6") != 0){
    exit(EXIT_FAILURE);
  }
  input >> this->width;
  input >> this->height;
  input >> this->maxVal;
  input.close();
  std::ifstream input2(name.append(".ppm"), std::ios::binary);
  input2.read((this->data), this->maxVal);
  input2.close();
}
char* ppm::returnData(){
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
