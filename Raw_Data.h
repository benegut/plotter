#ifndef RAW_DATA_H
#define RAW_DATA_H

#include <string>



class Raw_Data{

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
  void print();
  void print_Col_To_File(int);
  void print_Col_To_File(int, int);
  Raw_Data();
  Raw_Data(std::string);
  ~Raw_Data();
};


#endif
