#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Data.h"



void Data::setPathToFolder(std::string nameOfDataFolder){
  this->nameOfDataFolder = nameOfDataFolder;
}




void Data::getData(){
}




Data::Data(std::string nameOfDataFolder){
  Data::setPathToFolder(nameOfDataFolder);
  std::string exec = "#/bin/bash\ncd Measurements/" + nameOfDataFolder + "\nls -1 > ../../list.txt";
  system(exec.c_str());

  std::string filename;
  std::ifstream list("list.txt");
  
  while(getline(list, filename)){

    std::ifstream datafile("Measurements/" + nameOfDataFolder + "/" + filename);
    std::string line;

    while(getline(datafile, line, '\n')){

      std::stringstream ss(line);
      std::string num;

      while(getline(ss, num, '\t')){

	try{
	  Data::row.push_back(std::stod(num));
	}
	catch(std::exception& e){
	  break;
	}
      }
      Data::data.push_back(row);
    }
  }
}

