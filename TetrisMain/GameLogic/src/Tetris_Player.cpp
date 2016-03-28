#include "GameLogic/include/Tetris_Player.h"
#include <cmath>

Tetris_Player::Tetris_Player(){

	_score = 0;
	_level = 0;
	_time = 0;
	_speed = 1;
}

Tetris_Player::Tetris_Player(int score,int level, int time, int speed){
	
	_score = score;
	_level = level;
	_time = time;
	_speed = speed;
}

int Tetris_Player::getScore(){
	
	return _score;
}

int Tetris_Player::getSpeed(){
	
	return _speed;
}

int Tetris_Player::getTime(){
	
    return _time;
}

int Tetris_Player::getLevel(){
	
    return _level;
}

void Tetris_Player::computeSpeed(){
	
	_speed = 1 + trunc(_level/10);
}

void Tetris_Player::updateTime(int newTime){
	_time = newTime;
}

void Tetris_Player::updateScore(int numberOfRow){
	
	switch(numberOfRow){
		
		case 1: 
            _score += 40 * ( _level + 1 );
			break;
		
		case 2:
            _score += 100 * ( _level + 1 );
			break;
		
		case 3:
            _score += 300 * ( _level + 1 );
			break;
		
		case 4:
            _score += 1200 * ( _level + 1 );
			break;
		default:
            _score = -1;
			break;
	}
}

void Tetris_Player::display(){

    std::cout<<"Caracteristique du joueur :"<<std::endl;
    std::cout<<"    Score : "<<_score<<std::endl;
    std::cout<<"    Level : "<<_level<<std::endl;
    std::cout<<"    Time : "<<_time<<std::endl;
    std::cout<<"    Speed : "<<_speed<<std::endl;

}
