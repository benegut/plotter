#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include"Tools.h"


template<typename T>
void movingAverage_CArrays(int range, int size, T* arr, T* res){

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
    double dum = 0.0;

    while(counterDown >= lowEnd){
      dum += arr[counterDown];
      counterDown--;
    }

    while(counterUp < highEnd){
      dum += arr[counterUp];
      counterUp++;
    }


    res[arrCounter] = dum/(denom1 + denom2);
    arrCounter++;
  }
}
