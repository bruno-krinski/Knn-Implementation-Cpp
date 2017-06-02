#include <iostream>
#include <chrono>
#include <omp.h>
#include "ReadFeatures.h"
#include "Knn.h"

int main(int argc, char const *argv[]){
 
  std::chrono::high_resolution_clock::time_point init,end;
  init = std::chrono::high_resolution_clock::now();

  if(argc != 4){
   std::cout << "\33[1;31mWrong number of parameters!!!" << std::endl;
   std::cout << "Use mode: ./knn <train file> <test file> k\33[0m" 
             << std::endl;
   return -1;
  }

  int k = std::stoi(argv[3]);

  ReadFeatures train_data(argv[1]);
  ReadFeatures test_data(argv[2]);

  std::vector<FeatureVector> train_set;
  std::vector<FeatureVector> test_set;
  
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      train_data.readLabels();
      //train_data.printClasses();
      train_set = train_data.read();
    }
    
    #pragma omp section
    {
      test_data.readLabels();
      //test_data.printClasses();
      test_set = test_data.read();
    }
  }
 
  Knn my_knn(k,train_data.numClasses());
  my_knn.classify(train_set,test_set,train_data.getClasses());    

  end = std::chrono::high_resolution_clock::now();
  auto duration = 0;
  duration = std::chrono::duration_cast<std::chrono::seconds>(end-init).count();

  std::cout << "\33[1;32mTotal time: " << float(duration)/60.0 << " minutes\33[0m"
                                                               << std::endl;
  return 0;
}
