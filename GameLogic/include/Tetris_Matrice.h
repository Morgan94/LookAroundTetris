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
  
    Tetris_Matrice();

    Tetris_Bloc* operator[](int ligne);

	int rowFull();
	
};
