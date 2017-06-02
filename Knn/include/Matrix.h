#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class Matrix{

private:
  int nRows,nCols,mSize;
  T* matrix;

public:
  Matrix(int r,int c):nRows(r),nCols(c){
    mSize = nRows*nCols;
    matrix = new T [mSize];
    for(int i = 0; i < mSize; ++i){
      matrix[i] = (T)0;
    }
    
  }
  
  ~Matrix(){
    delete [] matrix;
  }

  void set(int r,int c,T e){
    matrix[r*nCols + c] = r;
  }

  T get(int r,int c){
    return matrix[r*nCols + c]; 
  }
  
  void add(int r, int c,T n){
    matrix[r*nCols+ + c] += n;
  }

  int size(){
    return mSize;
  }

  void print(std::vector<std::string> classes){
    
    int space;
    std::string c = "  ";
    for(unsigned int i = 0; i < classes.size(); ++i){
      c += "  " + classes[i] + " |";
    }
    c += "   R|";
    std::cout << c << std::endl;
    std::cout << "---------------------------------------------------------"
              << std::endl;
    for(int i = 0; i < nRows; ++i){
      std::cout << classes[i] << "|";
      for (int j = 0; j < nCols; ++j){
        space = matrix[i*nCols + j] > 0 ? (int) log10 ((double) matrix[i*nCols + j]) + 1 : 1;
        switch (space){
          case 1:
            std::cout << "   " << matrix[i*nCols + j] << "|";
            break;
          case 2:
            std::cout << "  " << matrix[i*nCols + j] << "|";                        
            break;
          case 3:
            std::cout << " " << matrix[i*nCols +j] << "|";
            break; 
          case 4:
            std::cout << matrix[i*nCols + j] << "|";
            break;
        }                                 
      }
      std::cout << std::endl;
    }
  }
};

#endif
