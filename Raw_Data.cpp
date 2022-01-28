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
  std::string exec = "#/bin/bash\nrm -f list.txt\ncd Measurements/" + Raw_Data::nameOfRaw_DataFolder + "\nls -1 > $OLDPWD/list.txt";
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

  double** matrix = new double*[Raw_Data::rowSize];
  for(int i = 0; i < Raw_Data::rowSize; ++i)
    matrix[i] = new double[Raw_Data::colSize];

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
   std::cout << "Data::read_Files() done." << std::endl;
 }



void Raw_Data::delete_Row(int rowIndex){
  for(int i=rowIndex;i!=Raw_Data::rowSize-1;i++)
    Raw_Data::raw_data[i] = Raw_Data::raw_data[i+1];
  //  delete [] Raw_Data::raw_data[Raw_Data::rowSize];
  --Raw_Data::rowSize;
}



void Raw_Data::clean_Up_Matrix(){

  for(int i=0; i!=Raw_Data::rowSize; i++){
    for(int j=0; j!=Raw_Data::colSize; j++){
      if(std::isnan(Raw_Data::raw_data[i][j])){
        Raw_Data::delete_Row(i);
        break;
      }
      else if(std::abs(Raw_Data::raw_data[i][j]) < 10e-10){
        Raw_Data::delete_Row(i);
        i--;
        break;
      }
    }
  }
  std::cout << "Data::clean_Up_Matrix() done." << std::endl;
}



void Raw_Data::print_To_Console(){
  for(int i=0; i!=Raw_Data::rowSize; i++){
    for(int j=0; j!=Raw_Data::colSize; j++)
      std::cout  << Raw_Data::raw_data[i][j] << " ";
    std::cout << std::endl;
    if(i==10){break;}
  }
}



void Raw_Data::print_To_File(int a=-1, int b=-1, int c=-1, int d=-1, int e=-1){

  if(a+b+c+d+e == -5)
    throw std::invalid_argument( "No Columns selected." );

  if(a>=Raw_Data::colSize || b>=Raw_Data::colSize || c>=Raw_Data::colSize || d>=Raw_Data::colSize || e>=Raw_Data::colSize)
    throw std::invalid_argument( "Selected Column to high." );

  std::ofstream file("raw_data_col_" + Raw_Data::nameOfRaw_DataFolder + ".csv");

  for(int i=0; i!=Raw_Data::rowSize; i++){
    for(int j=0; j!=Raw_Data::colSize; j++){
      if(j==a || j==b || j==c || j==d || j==e)
        file << Raw_Data::raw_data[i][j] << '\t';
    }
    file << '\n';
  }
  file.close();
}



void Raw_Data::plot_Col(int a=-1, int b=-1, int c=-1, int d=-1, int e=-1){

  Gnuplot gp;
  gp << "plot \"raw_data_col_" + Raw_Data::nameOfRaw_DataFolder + ".csv\" using 2:3 with points\n";
  //  gp << Raw_Data::raw_data;
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
  Raw_Data::clean_Up_Matrix();
  //Raw_Data::print_To_Console();
  Raw_Data::print_To_File(0,1,2);
  Raw_Data::plot_Col();
}



Raw_Data::~Raw_Data(){
  for (int i = 0; i < Raw_Data::rowSize; ++i)
    delete [] Raw_Data::raw_data[i];
  delete [] Raw_Data::raw_data;
}
