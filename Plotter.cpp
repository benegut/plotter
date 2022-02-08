#include <fftw3.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Raw_Data.h"
#include "gnuplot-iostream.h"
#include "persistence1d.hpp"




int main(int argc, char* argv[]){

  Raw_Data testData("280mA_Ingot/20220130-0001");
  //testData.get_Col(std::atoi(argv[1]));
  testData.get_Col(2);
  //testData.movingAverage(200);                   //saved in testData.polished_column
  //testData.low_Pass_Filter(0.01, 0);
  testData.find_Extrema(testData.column,0.6,0);



  testData.get_Col(1);

  int size = (int)testData.extrema.size();
  std::vector<std::vector<double>> extreme_Points_On_Signal(size, std::vector<double>(2));
  for(int i=0; i<size; i++){
    int ind = testData.extrema[i];
    extreme_Points_On_Signal[i] = {(double)ind, testData.column[ind]};
}


  Gnuplot gp;
  //gp << "set xrange [5000:10000]\n";
  gp << "set term png\n";
  gp << "set output \"x_deflection_with_data.png\"\n";
  gp << "plot '-' w l, '-' w p, '-' w l\n";
  gp.send1d(testData.column);
  gp << "\n";
  gp.send1d(extreme_Points_On_Signal);
  gp << "\n";
  testData.get_Col(2);
  gp.send1d(testData.column);
  gp << "set terminal x11\n";
  gp << "set output\n";
  gp << "replot\n";
}
