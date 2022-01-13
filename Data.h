#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data{

 private:
  std::string nameOfDataFolder;
  
 public:
  void setPathToFolder(std::string);

  long double **data;
  
  int getRowSize(std::string);

  int getColSize(std::string);

  void cleanUpMatrix(long double **, long double **);
  
  void getData();

  Data(std::string);
  
};


#endif
