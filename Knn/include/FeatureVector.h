#ifndef FEATURE_VECTOR_H
#define FEATURE_VECTOR_H

class FeatureVector{

private:
  std::vector<double> features;
  std::string feature_class;

public:
  FeatureVector(int tam){
    features.resize(tam+1);
  }

  ~FeatureVector(){
    features.clear();
  }

  inline void setFeature(int index,double feature){
    features[index+1] = feature;
  }
  
  inline double getFeature(int index){
    return features[index+1];
  }

  inline int getLabel(){
    return features[0];
  }

  inline void setLabel(unsigned int l){
    features[0] = l;
  }
  
  inline void setClass(std::string c){
    feature_class = c;
  }

  inline std::string getClass(){
    return feature_class;
  }

  inline int size(){
    return features.size(); 
  }

  void print(){
    std::cout << "\33[1;36mLabel: \33[0m" << features[0] << std::endl;
    //std::cout << "\33[1;36mFeatures: \33[0m" << std::endl;
    //for(unsigned int i = 0; i < features.size(); ++i){
    //  std::cout << features[i] << std::endl;
    //}
  }
};

#endif
