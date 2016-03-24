#ifndef __TETRIS__BLOC_
#define __TETRIS__BLOC_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

enum color {CYAN = 1, BLUE = 2, ORANGE = 3, YELLOW = 4, GREEN = 5, PURPLE = 6, RED = 7} ;


class Tetris_Bloc{

private:

	bool _check;
	int _value;  // Exemple pour bloc "rare" qui valent plus de point 
	color _color;

public:

	Tetris_Bloc();
	Tetris_Bloc(bool ch,int v,color c);

	bool isEmpty();
	int getValue();
	color getColor();
	void setCheck(bool c);
	void setValue(int v);
	void setColor(color c);

};

#endif
