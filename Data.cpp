#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Data.h"



void Data::set_Path_To_Folder(std::string nameOfDataFolder){
  Data::nameOfDataFolder = nameOfDataFolder;
}



void Data::get_Row_Size(){

  std::string filename;
  std::ifstream listfile("list.txt");
  int counterFiles = 0;
  int counterLines = 0;


  while(std::getline(listfile, filename)){

    std::ifstream datafile("Measurements/" + Data::nameOfDataFolder + "/" + filename);
    std::string lines;

    while(std::getline(datafile,lines)){
      counterLines++;
    }

    datafile.close();
    counterFiles++;
  }

  listfile.close();

  int arraySize = counterLines;// - counterFiles*3;
  //  int arraySize = counterLines; //ignore headerlines for now                               
  Data::rowSize = arraySize;
}





void Data::get_Col_Size(){

  int counterTabs = 0.0;
  std::string filename;
  std::ifstream listfile("list.txt");
  
  std::getline(listfile, filename);

  std::ifstream datafile("Measurements/" + Data::nameOfDataFolder + "/" + filename);
  std::string line;
  
  std::getline(datafile, line);
  
  std::stringstream ss(line);
  std::string num;
      
  while(std::getline(ss, num, '\t'))
    counterTabs++;

  Data::colSize = counterTabs;
}



void Data::generate_File_List(){
  std::string exec = "#/bin/bash\ncd Measurements/" + Data::nameOfDataFolder + "\nls -1 > ../../list.txt";
  system(exec.c_str());
  
}




void Data::read_Files(){

  double** matrix = new double*[Data::rowSize];
  for(int i = 0; i < Data::rowSize; ++i)
    matrix[i] = new double[Data::colSize];
  
  std::string filename;
  std::ifstream list("list.txt");
  int i = 0;
  
  while(getline(list, filename)){
    std::ifstream datafile("Measurements/" + Data::nameOfDataFolder + "/" + filename);
    std::string line;
    
    while(getline(datafile, line, '\n')){
      std::stringstream ss(line);
      std::string num;
      int j = 0;
      
      while(getline(ss, num, '\t')){	
	try{matrix[i][j] = stold(num);}
	catch(std::exception& e){i--;break;}
	j++;
      }
      i++;
    }
    datafile.close();
  }
  list.close();
  Data::data = matrix;
}



void Data::clean_Up_Matrix(){

  for(int i=0; i!=Data::rowSize; i++){
    for(int j=0; j!=Data::colSize; j++){
      

    }
  }
}



void Data::choose_Data(){
}



Data::Data(){
  std::cout << "*****************************************" << std::endl;
  std::cout << "No folder was selected. Call a Data object with the name of a folder in /Measurements." << std::endl;
  std::cout << "*****************************************" << std::endl;
}


 
Data::Data(std::string nameOfDataFolder){
  Data::set_Path_To_Folder(nameOfDataFolder);
  Data::get_Row_Size();
  Data::get_Col_Size();
  Data::generate_File_List();
  Data::read_Files();
  Data::clean_Up_Matrix();
}



Data::~Data(){
  for (int i = 0; i < Data::rowSize; ++i)
    delete [] Data::data[i];
  delete [] Data::data;
}
