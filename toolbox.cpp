#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include"toolbox.h"



int getArraySize(std::string pathToFileList, std::string pathToDataFolder){

  std::string filename;
  std::ifstream listfile(pathToFileList);
  int counterFiles = 0;
  int counterLines = 0;


  while(getline(listfile, filename)){

    std::ifstream datafile(pathToDataFolder + filename);
    std::string lines;

    //    std::cout << pathToDataFolder + filename << '\n';

    while(getline(datafile,lines)){
      //      std::cout << lines << '\n';
      counterLines++;}

    datafile.close();
    counterFiles++;
  }

  listfile.close();

  int arraySize = counterLines - counterFiles*3;
  //  int arraySize = counterLines; //ignore headerlines for now                
  return arraySize;
}






int getColumn(int col, int totalCols, double *arr){
  

  std::string filename;
  std::ifstream list("list.txt");
  int arrCounter = 0;
  int counter = 0;

  while(getline(list, filename)){
    
    std::ifstream datafile("/Measurements/20211202-0002/" + filename);
    std::string lines;
    int linecounter = 0;
    
    while(getline(datafile,lines, '\n')){

      std::stringstream ss(lines);

      while(getline(ss, lines, '\t')){

        if((counter-col)%totalCols == 0 && linecounter > 2){
          arr[arrCounter] = stold(lines);
          arrCounter++;
        }
        else if(col == 0 && counter%totalCols == 0 && linecounter > 2){
          arr[arrCounter] = arrCounter;
          arrCounter++;
        }
        counter++;
      }
      linecounter++;
    }
    datafile.close();

  }
  list.close();
  return arrCounter;
}





void writeToFile(int sieveSize){

  ofstream file("data.csv");

  string filename;
  ifstream listfile("/home/koyo/Documents/CPP/Plotter/list.txt");
  int arrCounter = 0;
  int counter = 0;

  while(getline(listfile, filename)){

    ifstream datafile("/home/koyo/Documents/Measurements/20211202-0002/" + file\
name);
    string lines;
    int linecounter = 0;

    while(getline(datafile,lines, '\n')){

      if(linecounter > 2 && counter%sieveSize == 0){
        file << lines << endl;
	arrCounter++;}

      counter++;
      linecounter++;
    }
    datafile.close();

  }
  listfile.close();
  cout << arrCounter << endl;

  file.close();
}



void writeToFile2(int sieveSize, int totalCols){

  ofstream file("data.csv");

  string filename;
  ifstream listfile("/home/koyo/Documents/CPP/Plotter/list.txt");
  int arrCounter = 0;
  int counter = 0;

  while(getline(listfile, filename)){

    ifstream datafile("/home/koyo/Documents/Measurements/20211202-0002/" + file\
name);
    string lines;
    int linecounter = 0;

    while(getline(datafile,lines, '\n')){

      if(linecounter > 2 && counter%sieveSize == 0){

	stringstream ss(lines);
        int position = 0;

	while(getline(ss,lines,'\t')){

          if(position == 0){
            file << arrCounter << '\t';
            position++;}
          else if(position == totalCols-1){
            file << lines << '\n';}
          else{
            file << lines << '\t';
            position++;}
        }
        arrCounter++;
      }

      counter++;
      linecounter++;
    }
    datafile.close();

  }
  listfile.close();
  cout << arrCounter << endl;

  file.close();
}



void writeArrayToFile(int size, double* arr1, double* arr2){

  ofstream file("data.csv");
  int arrCounter = 0;

  while(arrCounter < size){

    file << arrCounter << '\t' << arr1[arrCounter] << '\t' << arr2[arrCounter] \
<< '\n';
    arrCounter++;
  }
  file.close();

}



void idealLowPass(int cutoff, double* arr, double* res){



}

