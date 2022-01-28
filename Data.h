#ifndef DATA_H
#define DATA_H




class Data{

public:
  virtual void print_To_Console() = 0;
  virtual void print_To_File(int, int, int, int, int) = 0;
  virtual ~Data(){};

};


#endif
