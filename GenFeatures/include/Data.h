#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Image.h"

class Data{

private:
  std::string inFile,outFile;
  std::string path;
  std::vector<Image> data;
  std::vector<std::vector<unsigned int>> features;

public:
  Data(std::string i,std::string o,std::string p);
  void read();
  void extractFeatures();
  void normalize();
  void write();
  void print();  
};

#endif
