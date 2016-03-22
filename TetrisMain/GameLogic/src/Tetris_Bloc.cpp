#include "GameLogic/include/Tetris_Bloc.h"


Tetris_Bloc::Tetris_Bloc(){
	
	_check = false;
	_value = 1;
	_color = 1;
	
}

Tetris_Bloc::Tetris_Bloc(bool ch,int v,int c){
	
	_check = ch;
	_value = v;
	_color = c;
	
}

bool Tetris_Bloc::isEmpty(){
		
	return !_check;
}

void Tetris_Bloc::setCheck(bool ch){
	
	_check = ch;
}
	
int Tetris_Bloc::getValue(){
		
	return _value;
}

int Tetris_Bloc::getColor(){
		
	return _color;
}

void Tetris_Bloc::setValue(int v){
		
	_value = v;
}

void Tetris_Bloc::setColor(int c){
		
	_color = c;
}
 
