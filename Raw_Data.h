#ifndef RAW_DATA_H
#define RAW_DATA_H

#include <string>
#include "Data.h"


class Raw_Data: public Data{

 private:
  void err_No_Folder();
  std::string nameOfRaw_DataFolder;
  void set_Path_To_Folder(std::string);
  void generate_File_List();
  void get_Row_Size();
  void get_Col_Size();
  void read_Files();
  void delete_Row(int);
  void clean_Up_Matrix();

 public:
  int rowSize, colSize;
  double **raw_data;
  void print_To_Console();
  void print_To_File(int, int, int, int, int);
  void plot_Col(int,int, int, int, int);
  Raw_Data();
  Raw_Data(std::string);
  ~Raw_Data();
};


#endif
