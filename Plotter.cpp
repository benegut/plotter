#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Data.h"



int main(int argc, char* argv[]){
  
  Data testData("20211202-0002");
  std::cout << testData.data[1][1] << std::endl;
}
