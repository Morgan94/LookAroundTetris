#ifndef __TETRIS__TETRIS_BLOC__
#define __TETRIS__TETRIS_BLOC__

#include "lib/all.h"

class Tetris_Bloc
{
 private:
	
	bool _check;
	int _value;  // Exemple pour bloc "rare" qui valent plus de point 
	int _color;
    Hakurei::Mesh* mesh;
	
 public:
 
	Tetris_Bloc();
	Tetris_Bloc(bool ch,int v,int c);
 
	bool isEmpty();
	int getValue();
	int getColor();
	void setCheck(bool c);
	void setValue(int v);
	void setColor(int c);

};

#endif
