#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data{

 private:
  std::string nameOfDataFolder;
  std::string pathToFileList;
  
 public:
  void setPathToFolder(std::string nameOfDataFolder);

  std::vector<double> dataVec;

  void getData();

  Data(std::string nameOfDataFolder);
  
};


#endif
