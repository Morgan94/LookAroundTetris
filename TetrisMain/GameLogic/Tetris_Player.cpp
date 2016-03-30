#include "GameLogic/Tetris_Player.h"


Tetris_Player::Tetris_Player()
{
	score = 0;
	level = 1;
	lines = 0;
    start = 0;
	time = 0;
    deleteRow = 0;
    speed = SPEED_FACTOR * (float)(level);
}

float Tetris_Player::getSpeed(){

    return speed;
}

void Tetris_Player::startTime(){
    start = glfwGetTime();
}

void Tetris_Player::updateTime()
{
    time = glfwGetTime() - start;
}


void Tetris_Player::updateLevel()
{
    Uint32 oldLvl = level;
    level = (Uint32)(deleteRow/10) +1;

    if(oldLvl != level){
        updateSpeed();
    }
}

void Tetris_Player::addDeleteRow(Uint32 rows){

    deleteRow += rows;

}
void Tetris_Player::incrementScore(){

    score += 1;

}

void Tetris_Player::updateScore(Uint32 rows)
{
    switch(rows)
    {
		case 1:
			score += (40 * level);
			break;
		case 2:
			score += (100 * level);
			break;
		case 3:
			score += (300 * level);
			break;
		case 4:
			score += (1200 * level);
			break;
		default:
			break;
	}
	return;
}

void Tetris_Player::updateSpeed(){

    float inc = speed/3;
    speed += inc;
}

void Tetris_Player::udpate_Player(Uint32 count){

    addDeleteRow(count);
    updateScore(count);
    updateLevel();
    updateTime();

}

void Tetris_Player::display(){

    std::cout<<"Caracteristique du joueur :"<<std::endl;
    std::cout<<"    Score : "<<score<<std::endl;
    std::cout<<"    Level : "<<level<<std::endl;
    std::cout<<"    Time : "<<time<<std::endl;
    std::cout<<"    Speed : "<<speed<<std::endl;

}
