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



using namespace p1d;


int main(int argc, char* argv[]){

  Raw_Data testData("280mA_Ingot/20220130-0001");
  testData.get_Col(std::atoi(argv[1]));   //saved in testData.column

  // fftw_plan p;m
  // p = fftw_plan_r2r_1d(testData.rowSize, testData.column, output, FFTW_REDFT00,  FFTW_ESTIMATE|0);
  // fftw_execute(p);
  // fftw_destroy_plan(p);
  // std::cout << "fftw done." << std::endl;

  testData.movingAverage(200);  //saved in testData.polished_column

  Persistence1D p;
  p.RunPersistence(testData.polished_column);
  std::vector<TPairedExtrema> Extrema;
  p.GetPairedExtrema(Extrema,0.013);

  for(auto it = Extrema.begin(); it != Extrema.end(); it++){
    std::cout << "Persistence: " << (*it).Persistence
              << " minimum index: " << (*it).MinIndex
              << " maximum index: " << (*it).MaxIndex
              << std::endl;
  }


  std::vector<std::vector<double>> unsorted_points;
  for(auto it = Extrema.begin(); it != Extrema.end(); it++){
    int ind1 = (*it).MinIndex;
    unsorted_points.push_back({(double)ind1,testData.polished_column[ind1]});
    int ind2 = (*it).MaxIndex;
    unsorted_points.push_back({(double)ind2,testData.polished_column[ind2]});
  }


  std::vector<std::vector<double>> rearranged_Data(testData.raw_data.size(), std::vector<double>(3));
  for(int i=0; i<testData.raw_data.size(); i++){
    rearranged_Data[i].push_back(testData.raw_data[i][2]);
    rearranged_Data[i].push_back(testData.raw_data[i][3]);
    rearranged_Data[i].push_back(testData.raw_data[i][1]);
  }

  Gnuplot gp;
  // gp << "set xrange [0:2000]\n";
  // gp << "set yrange [-2000:2000]\n";
  //gp << "plot '-' with lines, '-' with lines\n";
  gp << "splot '-' with points\n";
  //  gp.send1d(testData.polished_column);
  //gp.send1d(testData.column);
  //gp.send1d(testData.polished_column);
  //gp.send1d(unsorted_points);
  gp.send2d(rearranged_Data);
}
