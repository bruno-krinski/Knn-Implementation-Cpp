#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image{

private:
  std::string fileName;
  std::string label;

public:
  Image(std::string name,std::string l):fileName(name),label(l){}
  inline std::string getLabel(){return label;}
  inline std::string getName(){return fileName;}
};

#endif
