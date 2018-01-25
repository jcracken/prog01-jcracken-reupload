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
  int i = 1;
  if(!(input.is_open())){
    std::cout << "File not found; try excluding the filename extension" << std::endl;
    exit(EXIT_FAILURE);
  }
  getline(input, temp);
  if(temp.compare("P6") != 0){
    std::cout << "File not correct format" << std::endl;
    exit(EXIT_FAILURE);
  }
  while(getline(input, temp) && i < 3){
    if(temp.at(0) == '#'); //skip
    else if(i == 1){
      std::istringstream iss(temp);
      iss >> this->width;
      iss >> this->height;
      i = 2;
    }
    else if(i == 2){
      std::istringstream iss(temp);
      iss >> this->maxVal;
      i = 3;
    }
  }
  input >> std::ws;
  this->data = new unsigned char[3*this->height*this->width];
  for(i = 0; i < 3*this->height*this->width; i++){
    this->data[i] = 0;
  }
  /*while(input){
    for(i = 0; i < 3*this->height*this->width; i++){
      input.get((char&)this->data[i]);
    }
  }*/
  input.read((char*)this->data, 3*this->height*this->width);
  input.close();
  writeData("temp");
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
void ppm::writeData(std::string name){
  std::ofstream out(name.append(".ppm"), std::ofstream::out | std::ofstream::binary);
  out << "P6\n" << this->width << " " << this->height << "\n" << this->maxVal << "\n";
  out.write((char*)this->data, this->width * this->height * 3);
  out.close();
}
