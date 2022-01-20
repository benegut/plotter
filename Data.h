#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data{

 private:
  void err_No_Folder();
  std::string nameOfDataFolder;
  void set_Path_To_Folder(std::string);
  void generate_File_List();
  void get_Row_Size();
  void get_Col_Size();
  void read_Files();
  void delete_Row(int);
  void clean_Up_Matrix();
  
 public:
  int rowSize, colSize;
  double **data;
  void choose_Data();
  void print();
  Data();
  Data(std::string);
  ~Data();
};


#endif
