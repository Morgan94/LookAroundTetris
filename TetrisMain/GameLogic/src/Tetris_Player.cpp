#include "GameLogic/include/Tetris_Player.h"

Tetris_Player(){

	_score = 0;
	_level = 0;
	_time = 0;
	_vitesse = 0;
}

Tetris_Player(int score,int level, int time, int vitesse){
	
	_score = score;
	_level = level;
	_time = time;
	_vitesse = vitesse;
}

int getScore(){
	
	return _score;
}

void updateTime(int newTime){
	_time = newTime;
}

void updateScore(int numberOfRow){
	
	switch(numberOfRow){
		
		case 1: 
			score += 40 * ( _level + 1 );
			break;
		
		case 2:
			score += 100 * ( _level + 1 );
			break;
		
		case 3:
			score += 300 * ( _level + 1 );
			break;
		
		case 4:
			score += 1200 * ( _level + 1 );
			break;
		default:
			break;
	}
}
