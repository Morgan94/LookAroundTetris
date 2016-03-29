#include "GameLogic/Tetris_Player.h"


Tetris_Player::Tetris_Player()
{
	score = 0;
	level = 1;
	lines = 0;
	start = glfwGetTime();
	time = 0;
	vitesse = SPEED_FACTOR * (float)(level);
}


void Tetris_Player::updateTime()
{
    time = glfwGetTime() - start;
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


