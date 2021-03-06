#include "ppm.h"

ppm::ppm(){
  this->data = NULL;
  this->width = 0;
  this->height = 0;
  this->maxVal = 0;
}
//loads in image data from filename argument
void ppm::readData(std::string name){
  std::ifstream input(name.append(".ppm"), std::ifstream::in | std::ifstream::binary);
  std::string temp;
  int i = 1;
  //verifies file existence
  if(!(input.is_open())){
    std::cout << "File not found; try excluding the filename extension" << std::endl;
    exit(EXIT_FAILURE);
  }
  //verifies file is of right format
  getline(input, temp);
  if(temp.compare("P6") != 0){
    std::cout << "File not correct format" << std::endl;
    exit(EXIT_FAILURE);
  }
  //parse header
  while(i < 3){
    getline(input, temp);
    //skip commented out lines
    if(temp.at(0) == '#');
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
  //remove any remaining whitespace
  input >> std::ws;
  //clear array used for loaded data, just in case
  this->data = new unsigned char[3*this->height*this->width];
  for(i = 0; i < 3*this->height*this->width; i++){
    this->data[i] = 0;
  }
  //load in data and close file
  input.read((char*)this->data, 3*this->height*this->width);
  input.close();
  //used for debugging purposes
  //writeData("temp");
}
//returns pixel data
unsigned char* ppm::returnData(){
  return this->data;
}
//returns image width
int ppm::returnWidth(){
  return this->width;
}
//returns image height
int ppm::returnHeight(){
  return this->height;
}
//returns max val variable
int ppm::returnMaxVal(){
  return this->maxVal;
}
//used for debugging
void ppm::writeData(std::string name){
  std::ofstream out(name.append(".ppm"), std::ofstream::out | std::ofstream::binary);
  //write header
  out << "P6\n" << this->width << " " << this->height << "\n" << this->maxVal << "\n";
  //write pixel data
  out.write((char*)this->data, this->width * this->height * 3);
  //close file
  out.close();
}
