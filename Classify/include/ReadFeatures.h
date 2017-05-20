#ifndef READ_FEATURES_H
#define READ_FEATURES_H

#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include "FeatureVector.h"

class ReadFeatures{

private:
  std::ifstream file;
  std::vector<std::string> feature_classes;

public:
  ReadFeatures(std::string name){
    file.open(name);
    if(!file.is_open()){
      std::cout << "\33[1;31mCould not open the file!\33[0m" << std::endl;
      exit(0);
    }
  }

  ~ReadFeatures(){
    file.close();
  }

  std::vector<FeatureVector> read(){
    int numlines, numfeatures;
    std::string line, buf;
    
    std::getline(file,line,' ');
    numlines = std::stoi(line);

    std::getline(file,line);
    numfeatures = std::stoi(line);

    std::vector<FeatureVector> data(numlines,FeatureVector(numfeatures));

    for(int i = 0; i < numlines; ++i){
      std::getline(file,line);
      std::stringstream sl(line);
      for(int j = 0; j < numfeatures; ++j){
        sl >> buf;
        data[i].setFeature(j,std::stod(buf));
      }
      sl >> buf;

      int index = std::find(feature_classes.begin(),
                            feature_classes.end(),buf) - feature_classes.begin();      
      //std::cout << index << std::endl;
      data[i].setLabel(index);
      data[i].setClass(buf);  
    }
    return data;
  }

  void readLabels(){
    for(int i = 0; i < 10; ++i){
      feature_classes.push_back(std::to_string(i));
    }
  }

  void readLabels(std::string labels_file){
    std::ifstream labels(labels_file);
    if(!labels.is_open()){
      std::cout << "\33[1;31mCould not open labels file!\33[0m" << std::endl;
      exit(0);
    }
    std::string line;
    while(std::getline(labels,line,'#')){
      std::getline(labels,line);
      std::stringstream ss(line);
      std::string buf;
      ss >> buf;
      feature_classes.push_back(buf);
    }
    labels.close();
  }

  inline unsigned int numClasses(){
    return feature_classes.size();
  }
  
  inline std::vector<std::string> getClasses(){
    return feature_classes;
  }

  void printClasses(){
    for(unsigned int i = 0; i < feature_classes.size(); ++i){
      std::cout << "Classe " << i << ":" << feature_classes[i] << std::endl;
    }
  }
};

#endif
