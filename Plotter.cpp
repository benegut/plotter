#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Raw_Data.h"



int main(int argc, char* argv[]){

  Raw_Data testData("320mA_Ingot/20220121-0001");

  system("./gnuplot-bash.sh");
}
