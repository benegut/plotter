#ifndef RAW_DATA_H
#define RAW_DATA_H

#include <vector>
#include <string>



class Raw_Data{

 private:
  int rowSize, colSize;
  std::string nameOfRaw_DataFolder;
  void err_No_Folder();
  void set_Path_To_Folder(std::string);
  void generate_File_List();
  void get_Row_Size();
  void get_Col_Size();
  void read_Files();
  void clean_up();


 public:
  std::vector<std::vector<double>> raw_data;
  std::vector<float> column;
  std::vector<float> polished_column;
  void print_To_Console();
  void print_To_File();
  void plot_Col(int);
  void get_Col(int);

  std::vector<std::vector<double>> extrema;
  void movingAverage(int);
  void find_Extrema(std::vector<float>, float, bool);
  void low_Pass_Filter(float, float);

  Raw_Data();
  Raw_Data(std::string);
  ~Raw_Data();
};


#endif
