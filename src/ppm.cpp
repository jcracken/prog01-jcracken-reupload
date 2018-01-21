#include "ppm.h"

ppm::ppm(){
  this->data = NULL;
  this->width = 0;
  this->height = 0;
  this->maxVal = 0;
}

void ppm::readData(std::string name){
  std::ifstream input(name.append(".ppm"), std::ifstream::in | std::ifstream::binary);
  std::string temp;
  if(!(input.is_open())){
    std::cout << "File not found" << std::endl;
    exit(EXIT_FAILURE);
  }
  getline(input, temp);
  if(temp.compare("P6") != 0){
    std::cout << "File not correct format" << std::endl;
    exit(EXIT_FAILURE);
  }
  input >> this->width;
  input >> this->height;
  input >> this->maxVal;
  this->data = new char[maxVal + 1];
  input.read(data,maxVal + 1);
  input.close();
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
