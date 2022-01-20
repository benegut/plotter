#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data{

 private:
  std::string nameOfDataFolder;
  void set_Path_To_Folder(std::string);
  int rowSize, colSize;
  void get_Row_Size();
  void get_Col_Size();
  void generate_File_List();
  void read_Files();
  void clean_Up_Matrix();
  
 public:
  double **data;
  void choose_Data();
   
  Data(std::string);
  
};


#endif
