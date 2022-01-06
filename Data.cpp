#include <string>
#include <vector>
#include <fstream>
#include "Data.h"



void Data::setPathToFolder(std::string nameOfDataFolder){
  this->nameOfDataFolder = nameOfDataFolder;
}

void Data::getData(){
}

Data::Data(std::string nameOfDataFolder){
  Data::setPathToFolder(nameOfDataFolder);
  std::string exec = "#/bin/bash\ncd Measurements/" + nameOfDataFolder + "\nls -1 > " + pathToFileList;
  system(exec.c_str());  
}
