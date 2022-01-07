#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data{

 private:
  std::string nameOfDataFolder;
  
 public:
  void setPathToFolder(std::string);

  typedef std::vector<double> Vec;
  typedef std::vector<Vec> Mat;

  Vec row;
  Mat data;
  
  void getData();

  Data(std::string);
  
};


#endif
