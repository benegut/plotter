#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "toolbox.h"



//change paths to filse here
#define SHELLSCRIPT "\
#/bin/bash \n\
cd Measurements/20211202-0002 \n\
ls -1 > ~/Documents/CPP/Plotter/list.txt"



int main(int argc, char* argv[]){

  system(SHELLSCRIPT);

  std::string pathToFileList = "list.txt";
  std::string pathToDataFolder = "/Measurements/20211202-0002/";

  int size = getArraySize(pathToFileList, pathToDataFolder);

  std::cout << size << '\n';
  //  double data[];
  double *data0 = new double[size];
  //double *data1 = new double[size];
  //double *data2 = new double[size];
  
  getColumn(0, 3, data0);
  //getColumn(1, 3, data1);
  //getColumn(2, 3, data2);


  //  int sieve = atoi(argv[1]);

  //  writeToFile(sieve);

  //  writeToFile2(sieve, 3);

  
  //double *averaged_Data_dum = new double[size];
  //double *averaged_Data1 = new double[size];
  //double* averaged_Data2 = new double[size];
  
  /*movingAverage_CArrays(1, size, data1, averaged_Data1);
  
  movingAverage(3500, size, averaged_Data_dum, averaged_Data1);

  movingAverage(2500, size, data2, averaged_Data_dum);
  */
  //  movingAverage(1, size, averaged_Data_dum, averaged_Data2);

  //writeToFile3(size, data1, data2);

  //std::cout << size << std::endl;
  
  system("./gnuplot-bash.sh");
}
