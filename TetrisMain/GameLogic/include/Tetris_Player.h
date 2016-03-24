#ifndef __TETRIS__BLOC_
#define __TETRIS__BLOC_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tetris_Bloc.h"

class Tetris_Player{

private:
	
	int _score;
	int _level;
	int _time;
	int _vitesse;

public:

	Tetris_Player();
	Tetris_Player(int score,int level, int time, int vitesse);
	
	int getScore();
	void updateTime(int newTime);
	void updateScore(int newTime);

};

#endif
