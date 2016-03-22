#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tetris_Bloc.h"

#define width 24
#define height 24

class Tetris_Matrice{

 private:
 
  Tetris_Bloc** _mat;
  int _nl = height;
  int _nc = width;

 public:
  
	void deleteRow(int num);
    Tetris_Matrice(int nl,int nc);
	void display();
    Tetris_Bloc** operator[](int ligne);
	int rowFull();
	
};
