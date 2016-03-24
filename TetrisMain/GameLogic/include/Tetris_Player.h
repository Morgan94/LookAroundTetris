#ifndef __TETRIS__PLAYER_
#define __TETRIS__PLAYER_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

class Tetris_Player{

private:
	
	int _score;
	int _level;
	int _time;
	int _speed;

public:

	Tetris_Player();
	Tetris_Player(int score,int level, int time, int vitesse);
	
	int getScore();
	int getSpeed();
	int getLevel();
	int getTime();
	void computeSpeed();
	void updateTime(int newTime);
    void updateScore(int numberOfRow);
    void display();

};

#endif
