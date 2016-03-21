#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Tetris_Bloc{

 private:
	
	bool _check;
	int _value;  // Exemple pour bloc "rare" qui valent plus de point 
	int _color;
	
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
