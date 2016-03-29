#ifndef __TETRIS__PLAYER__
#define __TETRIS__PLAYER__


#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"

#define SPEED_FACTOR        0.1


class Tetris_Player
{
public:

	Uint32 score;
	Uint32 level;
	Uint32 lines;
	double start;
	double time;
	float vitesse;


	Tetris_Player();
	void updateTime();
	void updateScore(Uint32 rows = 1);

};


#endif

