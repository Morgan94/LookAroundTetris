#ifndef __TETRIS__PLAYER__
#define __TETRIS__PLAYER__


#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"

#define SPEED_FACTOR        0.05


class Tetris_Player
{
public:

	Uint32 score;
	Uint32 level;
	Uint32 lines;
	double start;
	double time;
    float speed;
    Uint32 deleteRow;

	Tetris_Player();

    float getSpeed();

    void startTime();
	void updateTime();
    void updateLevel();
    void updateSpeed();
	void updateScore(Uint32 rows = 1);
    void udpate_Player(Uint32 count);

    void addDeleteRow(Uint32 rows);
    void incrementScore();

    void display();

};


#endif

