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

  Raw_Data testData("280mA_Ingot/20220203-0001");
  testData.get_Col(std::atoi(argv[1]));            //saved in testData.column
  //testData.movingAverage(200);                   //saved in testData.polished_column
  testData.low_Pass_Filter(0.01, -2.7);
  //testData.find_Extrema(testData.column,0.6,0);


  // fftw_plan p;
  // p = fftw_plan_r2r_1d(testData.rowSize, testData.column, output, FFTW_REDFT00,  FFTW_ESTIMATE|0);
  // fftw_execute(p);
  // fftw_destroy_plan(p);
  // std::cout << "fftw done." << std::endl;



  // std::vector<std::vector<double>> rearranged_Data(testData.raw_data.size(), std::vector<double>(3));
  // for(int i=0; i<testData.raw_data.size(); i++){
  //   rearranged_Data[i][0] = testData.raw_data[i][1];
  //   rearranged_Data[i][1] = testData.raw_data[i][2];
  //   rearranged_Data[i][2] = testData.raw_data[i][4];
  // }

  // int col = 2;
  // double max = rearranged_Data[0][col];
  // double min = rearranged_Data[0][col];
  // for(auto i: rearranged_Data){
  //   if(max<i[col])
  //     max = i[col];
  //   if(min>i[col])
  //       min = i[col];
  //   }

  // for(int i=0; i<rearranged_Data.size(); i++){
  //   rearranged_Data[i][col] -= max;
  //   rearranged_Data[i][col] = rearranged_Data[i][col]/(-(std::abs(min)-std::abs(max)));
  // }



  // std::ofstream outfile("rearranged_Data.txt");
  // for(auto i: rearranged_Data){
  //   for(auto j: i)
  //     outfile << j << '\t';
  //   outfile << '\n';
  // }
  // outfile.close();

  Gnuplot gp;
  //gp << "set xrange [0:2000]\n";
  // gp << "set yrange [-2000:2000]\n";
  gp << "plot '-' w l\n";
  //gp << "plot '-' w l, '-' w l\n";
  //gp << "set palette defined (0 \"blue\", 1 \"red\")\nsplot '-' using 1:2:3 w image\n";
  //gp << "plot '-' with lines\n";
  //  gp.send1d(testData.polished_column);
  //gp.send1d(testData.column);
  //gp.send1d(testData.polished_column);
  //gp.send1d(testData.column);
  //gp << "\n";
  gp.send1d(testData.polished_column);
  //gp.send2d(rearranged_Data);
  //gp."splot "" u 2:3:4:"
}
