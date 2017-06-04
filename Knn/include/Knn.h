#ifndef KNN_H
#define KNN_H

#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Matrix.h"
#include "FeatureVector.h"

int guess_class(std::vector<int>& classes);

void find_classes(std::vector<int>& classes,std::vector<double>& distances,
                  std::vector<FeatureVector>& t,int k);

double euclidian_dist(FeatureVector& v,FeatureVector& u);

class Knn{

private:
  unsigned int k;
  unsigned int numClasses;
  //double hit_rate;
  
public:
  Knn(unsigned int i,unsigned int n):k(i),numClasses(n){}
  
  void classify(std::vector<FeatureVector>& train,
                std::vector<FeatureVector>& test,
                std::vector<std::string> myClasses){
    //int hit_hate = 0;
    double rejection = 0;
    double hit_rate = 0;
    unsigned int x = numClasses;
    unsigned int y = x+1;	
    Matrix<int> confusion(x,y);
    for(unsigned int i = 0; i < test.size(); ++i){
      std::vector<int> classes(numClasses);
      std::vector<double> distances(train.size());
      for(unsigned int j = 0; j < train.size(); ++j){
        distances[j] = euclidian_dist(train[j],test[i]);
        //train[j].print();
      }
      find_classes(classes,distances,train,k);
      int try_class = guess_class(classes);
      confusion.add(test[i].getLabel(),try_class,1);
      if (try_class == test[i].getLabel()){
        hit_rate++;
      } else if(try_class == 10){
        rejection++;	
      } 
    } 
    std::cout << "\33[1;32mConfusion Matrix: \33[0m" << std::endl;
    confusion.print(myClasses);
    std::cout << "\33[1;32mHit Rate: " 
              << (hit_rate/(float)test.size())*100
              << "%\33[0m"
              << std::endl;
    std::cout << "\33[1;32mRejection Rate: "
	      << (rejection/(float)test.size())*100
              << "%\33[0m"
              << std::endl;
  }
};

double euclidian_dist(FeatureVector& v,
                      FeatureVector& u){
  double sum = 0.0;
  for(int i = 0; i < v.size(); ++i){
    sum += fabs(v.getFeature(i) - u.getFeature(i));
  }
  return sum; 
}

void find_classes(std::vector<int>& classes,
                  std::vector<double>& distances,
                  std::vector<FeatureVector>& t,int k){
  int pos;

  for(int i = 0; i < k; ++i){
    pos = std::min_element(distances.begin(),distances.end()) - distances.begin();
    //std::cout << t[pos].getLabel() << std::endl;
    distances[pos] = 10.0;
    classes[t[pos].getLabel()] += 1; 
  }
}

int guess_class(std::vector<int>& classes){

  int pos = std::max_element(classes.begin(),classes.end()) - classes.begin();
  int element = classes[pos];
  classes[pos] = 0;
  if (std::find(classes.begin(),classes.end(),element) == classes.end()){
    return pos;
  } else {
    return 10;
  }
}

#endif
