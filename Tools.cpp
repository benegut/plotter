#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
//#include <fftw3.h>
#include"Raw_Data.h"
#include <vector>
#include "persistence1d.hpp"

using namespace p1d;



void Raw_Data::movingAverage(int range){

  int size = (int)Raw_Data::column.size();
  std::vector<float> res(size);
  int low = (range%2) == 0 ? range/2 : (range-1)/2;
  int high = (range%2) == 0 ? range/2 : (range+1)/2;
  int arrCounter = 0;

  while(arrCounter < size){

    int counterUp = arrCounter;
    int counterDown = arrCounter-1;
    int lowEnd = arrCounter - low < 0 ? 0 : arrCounter-low;
    int highEnd = arrCounter+high >= size ? size : arrCounter + high;
    int denom1 = lowEnd == 0 ? arrCounter : low;
    int denom2 = highEnd == size ? size - arrCounter : high;
    float dum = 0.0;

    while(counterDown >= lowEnd){
      dum += Raw_Data::column[counterDown];
      counterDown--;
    }

    while(counterUp < highEnd){
      dum += Raw_Data::column[counterUp];
      counterUp++;
    }

    res[arrCounter] = dum/(denom1 + denom2);
    arrCounter++;
  }
  Raw_Data::polished_column = res;
}



void Raw_Data::find_Extrema(std::vector<float> input, float persistence, bool PRINT_FLAG){

  Persistence1D p;
  p.RunPersistence(input);
  std::vector<TPairedExtrema> Extrema;
  p.GetPairedExtrema(Extrema,0.6);

  if(PRINT_FLAG){
    for(auto it = Extrema.begin(); it != Extrema.end(); it++){
      std::cout << "Persistence: " << (*it).Persistence
                << " minimum index: " << (*it).MinIndex
                << " maximum index: " << (*it).MaxIndex
                << std::endl;
    }
  }


  std::vector<int> extrema(2*Extrema.size());
  std::vector<std::vector<double>> extreme_Points(2*Extrema.size(), std::vector<double>(2));
  int i = 0;
  for(auto it = Extrema.begin(); it != Extrema.end(); it++){
    int ind1 = (*it).MinIndex;
    extreme_Points[i] = {(double)ind1,input[ind1]};
    extrema[i] = ind1;
    ++i;
    int ind2 = (*it).MaxIndex;
    extreme_Points[i] = {(double)ind2,input[ind2]};
    extrema[i] = ind2;
    ++i;
  }
  Raw_Data::extrema = extrema;
  Raw_Data::extreme_Points = extreme_Points;
}



void Raw_Data::low_Pass_Filter(float beta, float y0){

  if(beta<0 || beta>1)
    throw std::invalid_argument( "Raw_Data::low_Pass_Filter(): beta must be within 0 and 1." );

  int size = (int)Raw_Data::column.size();
  std::vector<float> y(size);
  y[0] = y0;
  for(int i=1; i<size; i++)
    y[i] = beta*Raw_Data::column[i] + (1-beta)*y[i-1];
  Raw_Data::polished_column = y;
}
