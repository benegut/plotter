//#include <boost/numeric/ublas/matrix.hpp>
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



int Data::getRowSize(std::string nameOfDataFolder){

  std::string filename;
  std::ifstream listfile("list.txt");
  int counterFiles = 0;
  int counterLines = 0;


  while(std::getline(listfile, filename)){

    std::ifstream datafile("Measurements/" + nameOfDataFolder + "/" + filename);
    std::string lines;

    //std::cout << "/Measurements/" + nameOfDataFolder + "/" + filename << '\n';                                    

    while(std::getline(datafile,lines)){
      //      std::cout << lines << '\n';
      try{
	stod()
	counterLines++;
	
      }
    }

    datafile.close();
    counterFiles++;
  }

  listfile.close();

  int arraySize = counterLines;// - counterFiles*3;
  //  int arraySize = counterLines; //ignore headerlines for now                               
  return arraySize;
}





int Data::getColSize(std::string nameOfDataFolder){

  int counterTabs = 0.0;
  std::string filename;
  std::ifstream listfile("list.txt");
  
  std::getline(listfile, filename);

  std::ifstream datafile("Measurements/" + nameOfDataFolder + "/" + filename);
  std::string line;
  
  std::getline(datafile, line);
  
  std::stringstream ss(line);
  std::string num;
      
  while(std::getline(ss, num, '\t'))
    counterTabs++;

  return counterTabs;
}







void Data::getData(){
}




Data::Data(std::string nameOfDataFolder){

  int rowSize = Data::getRowSize(nameOfDataFolder);
  int colSize = Data::getColSize(nameOfDataFolder);

  long double** matrix = new long double*[rowSize];
  for(int i = 0; i < rowSize; ++i){
    matrix[i] = new long double[colSize];
  }
  
  Data::setPathToFolder(Data::nameOfDataFolder);
  std::string exec = "#/bin/bash\ncd Measurements/" + nameOfDataFolder + "\nls -1 > ../../list.txt";
  system(exec.c_str());

  std::string filename;
  std::ifstream list("list.txt");
  int i = 0;
  
  while(getline(list, filename)){

    std::ifstream datafile("Measurements/" + nameOfDataFolder + "/" + filename);
    std::string line;
    
    while(getline(datafile, line, '\n')){

      std::stringstream ss(line);
      std::string num;
      int j = 0;

      while(getline(ss, num, '\t')){

	try{
	  matrix[i][j] = stold(num);
	}
	catch(std::exception& e){
	  break;
	}
	j++;
      }
      i++;
    }
    datafile.close();
  }
  list.close();
  Data::data = matrix;
}

