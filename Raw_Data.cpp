#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include "gnuplot-iostream.h"
#include "Raw_Data.h"
#include "Data.h"


void Raw_Data::err_No_Folder(){
  std::cout << "*****************************************" << std::endl;
  std::cout << "No folder was selected. Call a Raw_Data object with the name of a folder in /Measurements." << std::endl;
  std::cout << "*****************************************" << std::endl;
}



void Raw_Data::set_Path_To_Folder(std::string nameOfRaw_DataFolder){
  Raw_Data::nameOfRaw_DataFolder = nameOfRaw_DataFolder;
}



void Raw_Data::generate_File_List(){

  // std::string exec = "#/bin/bash\nrm -f list.txt\ncd Measurements/" + Raw_Data::nameOfRaw_DataFolder + "\nls -1 > $OLDPWD/list.txt";
  // system(exec.c_str());

  std::string exec = "#/bin/bash\nrm -f list.txt\ncd Measurements/" + Raw_Data::nameOfRaw_DataFolder + "\nfind . -type f -iname \"*_1[0-3].txt\" > $OLDPWD/list.txt";
  system(exec.c_str());
}



void Raw_Data::get_Row_Size(){

  std::string filename;
  std::ifstream listfile("list.txt");
  int counterFiles = 0;
  int counterLines = 0;

  while(std::getline(listfile, filename)){
    std::ifstream raw_datafile("Measurements/" + Raw_Data::nameOfRaw_DataFolder + "/" + filename);
    std::string lines;

    while(std::getline(raw_datafile,lines))
      counterLines++;

    raw_datafile.close();
    counterFiles++;
  }
  listfile.close();
  Raw_Data::rowSize = counterLines;
}



void Raw_Data::get_Col_Size(){

  int counterTabs = 0.0;
  std::string filename;
  std::ifstream listfile("list.txt");

  std::getline(listfile, filename);

  std::ifstream raw_datafile("Measurements/" + Raw_Data::nameOfRaw_DataFolder + "/" + filename);
  std::string line;

  std::getline(raw_datafile, line);

  std::stringstream ss(line);
  std::string num;

  while(std::getline(ss, num, '\t'))
    counterTabs++;

  Raw_Data::colSize = counterTabs;
}



void Raw_Data::read_Files(){

  std::vector<std::vector<double>> matrix(Raw_Data::rowSize, std::vector<double>(Raw_Data::colSize));

  std::string filename;
  std::ifstream list("list.txt");
  int i = 0;

  while(getline(list, filename)){
    std::ifstream raw_datafile("Measurements/" + Raw_Data::nameOfRaw_DataFolder + "/" + filename);
    std::string line;

    while(getline(raw_datafile, line, '\n')){
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
    raw_datafile.close();
  }
  list.close();
  Raw_Data::raw_data = matrix;
  std::cout << "Raw_Data::read_Files() done." << std::endl;
}



void Raw_Data::clean_up(){

 repeat:
  for(auto i = Raw_Data::raw_data.begin(); i<Raw_Data::raw_data.end(); i++){
    for(auto j: *i){
      if(abs(j)<10e-14){
        Raw_Data::raw_data.erase(i);
        goto repeat;
      }
    }
  }
  std::cout << "Raw_Data::clean_up() done." << std::endl;
}



void Raw_Data::print_To_Console(){
  for(auto i: Raw_Data::raw_data){
    for(auto j: i)
      std::cout  << j << " ";
    std::cout << std::endl;
    if(i==Raw_Data::raw_data[10]){break;}
  }
}



void Raw_Data::print_To_File(){

  std::ofstream file("tmp.csv");

  for(auto i: Raw_Data::raw_data){
    for(auto j: i)
      file << j << '\t';
    file << '\n';
  }
  file.close();
}



void Raw_Data::plot_Col(int a){

  Raw_Data::print_To_File();
  Gnuplot gp;
  gp << "plot \"tmp.csv\" using " + std::to_string(a+1) + " with lines\n";
}



void Raw_Data::get_Col(int col){

  if(col >= (int)Raw_Data::raw_data[0].size())
    throw std::invalid_argument( "Raw_Data::get_col(): Selected Column to high." );

  std::vector<float> array(Raw_Data::rowSize);

  for(int i=0; i<(int)Raw_Data::raw_data.size(); i++)
    array[i] =  (float)Raw_Data::raw_data[i][col];

  Raw_Data::column = array;
}



Raw_Data::Raw_Data(){
  Raw_Data::err_No_Folder();
}



Raw_Data::Raw_Data(std::string nameOfRaw_DataFolder){
  Raw_Data::set_Path_To_Folder(nameOfRaw_DataFolder);
  Raw_Data::get_Row_Size();
  Raw_Data::get_Col_Size();
  Raw_Data::generate_File_List();
  Raw_Data::read_Files();
  Raw_Data::clean_up();
  Raw_Data::print_To_File();
}



Raw_Data::~Raw_Data(){}
