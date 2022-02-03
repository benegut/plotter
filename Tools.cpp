#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
//#include <fftw3.h>
#include"Raw_Data.h"
#include <vector>



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



void Raw_Data::find_Extrema(){

  int size = (int)Raw_Data::polished_column.size();
  int dif = 1;
  std::vector<int> min_max;

  if (Raw_Data::polished_column[0] > Raw_Data::polished_column[dif])
    min_max.push_back(0);
  else if (Raw_Data::polished_column[0] < Raw_Data::polished_column[dif])
    min_max.push_back(0);

  for(int i=dif; i < size-1-dif; i++){

    if ((Raw_Data::polished_column[i-dif] > Raw_Data::polished_column[i]) and
        (Raw_Data::polished_column[i] < Raw_Data::polished_column[i+dif]))
      min_max.push_back(i);
    else if ((Raw_Data::polished_column[i-dif] < Raw_Data::polished_column[i]) and
             (Raw_Data::polished_column[i] > Raw_Data::polished_column[i+dif]))
      min_max.push_back(i);
  }

  if (Raw_Data::polished_column[size-1] > Raw_Data::polished_column[size-dif])
    min_max.push_back(size-1);
  else if (Raw_Data::polished_column[size-1] < Raw_Data::polished_column[size-dif])
    min_max.push_back(size-1);


  std::vector<std::vector<double>> extrema(min_max.size(), std::vector<double>(2));

  for(int i=0; i<(int)min_max.size(); i++){
    extrema[i][0] = (double)min_max[i];
    extrema[i][1] = Raw_Data::polished_column[min_max[i]];
  }
  Raw_Data::extrema = extrema;
}
