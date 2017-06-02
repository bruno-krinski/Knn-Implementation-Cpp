#include <omp.h>
#include <chrono>
#include "Data.h"

int main(int argc, char const *argv[]){
  
  std::chrono::high_resolution_clock::time_point init,end;
  init = std::chrono::high_resolution_clock::now();

  if(argc != 7){
    std::cout << "\33[1;31mWrong number of parameters!" << std::endl;
    std::cout << "Use mode: ./genFeatures <path to train file> <path to train images> <path to val file> <path to val images> <path to test file> <path to test images>\33[0m" << std::endl;
    exit(0);
  } 

  Data train(argv[1],"train.txt",argv[2]);
  Data val(argv[3], "val.txt",argv[4]);
  Data test(argv[5], "test.txt",argv[6]);
  #pragma omp parallel sections
  { 
    #pragma omp section
    train.read();
    #pragma omp section
    val.read();
    #pragma omp section
    test.read();
  }

  train.extractFeatures();
  val.extractFeatures();
  test.extractFeatures();
  std::vector<unsigned int> min(48,100),max(48,0);
  find_minmax(min,max,train.features);
  train.normalize(min,max);
  val.normalize(min,max);
  test.normalize(min,max);

  end = std::chrono::high_resolution_clock::now();
  auto duration = 0.0;
  duration = std::chrono::duration_cast<std::chrono::seconds>(end-init).count();
  std::cout << "\33[1;32mTotal time: " 
            << duration
            << " seconds\33[0m"
            << std::endl;  
  return 0;
}
