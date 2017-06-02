#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Image.h"

void find_minmax(std::vector<unsigned int>& min,
                 std::vector<unsigned int>& max,
                 std::vector<std::vector<unsigned int>>& features);

class Data{

public:
  std::string inFile,outFile;
  std::string path;
  std::vector<Image> data;
  std::vector<std::vector<unsigned int>> features;

public:
  Data(std::string i,std::string o,std::string p);
  void read();
  void extractFeatures();
  void normalize(std::vector<unsigned int>& min, std::vector<unsigned int>& max);
  void write();
  void print();  
};

#endif
