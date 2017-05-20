#include "Data.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp>

unsigned int chainCode(cv::Point& v,cv::Point& u);

void chainCodes(std::vector<cv::Point>& contour,std::vector<unsigned int>& cc);

void cutImage(cv::Mat& image,std::vector<cv::Mat>& cuts);

void differenceChainCodes(std::vector<unsigned int>& cc,
                          std::vector<unsigned int>& dcc);

void concatVector(std::vector<unsigned int>& v,
                  std::vector<unsigned int>& u);

Data::Data(std::string i,std::string o,std::string p){
  inFile = i;
  outFile = o;
  path = p;
}

void Data::read(){
  std::ifstream input(inFile);
  
  if(!input.is_open()){
    std::cout << "\33[1;31Could not open " << inFile << "!!!\33[0m" 
                                                     << std::endl;
    exit(0);
  }
  std::string line;
  while(std::getline(input,line)){
    std::stringstream ss(line);
    std::string name,label;
    ss >> name;
    ss >> label;
    Image i(name,label);
    data.push_back(i);
  }
}

void Data::print(){
  for(unsigned int i = 0; i < data.size();++i){
    std::cout << "Image file: " << data[i].getName()
              << "Label: " << data[i].getLabel() << std::endl;
  }
  std::cout << "Number of images: " << data.size() << std::endl;
}

void Data::extractFeatures(){

  for(unsigned int i = 0; i < data.size(); ++i){
    //std::cout << i << std::endl;
   
    cv::Mat image;  
    image = cv::imread(path+"/"+data[i].getName(),0);
    
    if (!image.data){
      std::cout << "\33[1;31mCould not open or find the image "
                << data[i].getName() << "\33[0m" << std::endl;
      exit(0); 
    }
 
    Canny(image, image, 100, 200, 3);

    std::vector<cv::Mat> cuts(6); 
    cutImage(image,cuts);
    
    std::vector<unsigned int> histogram(48,0);
    for(unsigned int j = 0; j < cuts.size(); ++j){
      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hierarchy;
      cv::findContours(cuts[j],contours,hierarchy,CV_RETR_LIST,
                                                  CV_CHAIN_APPROX_NONE,
                                                  cv::Point(0,0));
      std::vector<unsigned int> totChainCodes;
      for(unsigned int k = 0; k < contours.size(); ++k){
        std::vector<unsigned int> chain_codes;
        chainCodes(contours[k],chain_codes);
        concatVector(totChainCodes,chain_codes);  
      }
      //std::vector<unsigned int> diffChainCodes;
      //differenceChainCodes(totChainCodes,diffChainCodes);
      for(unsigned int k = 0; k < 8; ++k){
        histogram[j*8+k] = std::count(totChainCodes.begin(),
                                      totChainCodes.end(),k);
      }
    }
    features.push_back(histogram);     
  }
}

void Data::normalize(){
  
  std::ofstream output(outFile);
  
  if(!output.is_open()){
    std::cout << "\33[1;31mCould not open the output file\33[0m;" << std::endl;
    exit(0);
  }
  
  output << std::to_string(data.size()) + " " + std::to_string(48) + "\n";
  
  std::vector<unsigned int> min(48,100);
  std::vector<unsigned int> max(48,0);

  for(unsigned int i = 0; i < features.size(); ++i){
    for(unsigned int j = 0; j < features[i].size(); ++j){
      if(features[i][j] > max[j]){
        max[j] = features[i][j];
      }
      if(features[i][j] < min[j]){
        min[j] = features[i][j];
      }   
    }
  }
    
  for(unsigned int i = 0; i < features.size(); ++i){
    for(unsigned int j = 0; j < features[i].size(); ++j){
      int a = features[i][j] - min[j];
      int b = max[j] - min[j];
      double aux = double(a)/double(b);
      output << std::to_string(aux) << " ";
    }
    output << data[i].getLabel() + "\n";
  }
}

void cutImage(cv::Mat& image,std::vector<cv::Mat>& cuts){
  
  cv::Mat cut0(image,cv::Rect(0,0,image.cols/2,image.rows/3));
  cv::Mat cut1(image,cv::Rect(0,image.rows/3,image.cols/2,image.rows/3));
  cv::Mat cut2(image,cv::Rect(0,2*image.rows/3,image.cols/2,image.rows/3));
  cv::Mat cut3(image,cv::Rect(image.cols/2,0,image.cols/2,image.rows/3));
  cv::Mat cut4(image,cv::Rect(image.cols/2,image.rows/3,image.cols/2,
                                                        image.rows/3));
  cv::Mat cut5(image,cv::Rect(image.cols/2,2*image.rows/3,image.cols/2,
                                                          image.rows/3));
  cut0.copyTo(cuts[0]);
  cut1.copyTo(cuts[1]);
  cut2.copyTo(cuts[2]);
  cut3.copyTo(cuts[3]);
  cut4.copyTo(cuts[4]);
  cut5.copyTo(cuts[5]);
}

void chainCodes(std::vector<cv::Point>& contour,std::vector<unsigned int>& cc){
  
  for(unsigned int i = 1; i < contour.size(); ++i){
    unsigned int aux = chainCode(contour[i-1],contour[i]);
    cc.push_back(aux);  
  }
}

unsigned int chainCode(cv::Point& v, cv::Point& u){
  if ((v.x == u.x) && (v.y > u.y)){
    return 0;
  } else if ((v.x < u.x) && (v.y > u.y)){
    return 7;
  } else if ((v.x < u.x) && (v.y == u.y)){
    return 6;
  }else if ((v.x < u.x) && (v.y < u.y)){
    return 5;
  } else if ((v.x == u.x) && (v.y < u.y)){
    return 4;
  } else if ((v.x > u.x) && (v.y < u.y)){
    return 3;
  } else if ((v.x > u.x) && (v.y == u.y)){
    return 2;
  } else if ((v.x > u.x) && (v.y > u.y)){
    return 1;
  }
  return 0;
}

void differenceChainCodes(std::vector<unsigned int>& cc,
                          std::vector<unsigned int>& dcc){
  for(unsigned int i = 1; i < cc.size(); ++i){
    if (cc[i] >= cc[i-1]){
      dcc.push_back((cc[i] - cc[i-1]));
    } else {
      dcc.push_back((8-fabs(cc[i]-cc[i-1])));
    }  
  }
}

void concatVector(std::vector<unsigned int>& v,std::vector<unsigned int>& u){
  for(unsigned int i = 0; i < u.size(); ++i){
    v.push_back(u[i]);
  }
}
