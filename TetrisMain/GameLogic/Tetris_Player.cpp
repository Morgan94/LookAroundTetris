#include "GameLogic/Tetris_Player.h"


Tetris_Player::Tetris_Player()
{
    score = 0;
    level = 1;
    lines = 0;
    start = 0;
    time = 0;
    deletedRows = 0;
    speed = SPEED_FACTOR;
}

void Tetris_Player::startTime()
{
    start = glfwGetTime();
    time = 0;
}

void Tetris_Player::updateTime()
{
    time = glfwGetTime() - start;
}

void Tetris_Player::updateLevel()
{
    Uint32 oldLvl = level;
    level = deletedRows / 5 + 1;
    if(oldLvl != level) increaseSpeed();
}

void Tetris_Player::addDeletedRows(Uint32 rows)
{
    deletedRows += rows;
}

void Tetris_Player::incrementScore()
{
    score += (level * 3);
}

void Tetris_Player::updateScore(Uint32 rows)
{
    addDeletedRows(rows);
    updateLevel();

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

void Tetris_Player::increaseSpeed()
{
    speed *= 1.3;
}

void Tetris_Player::udpatePlayer()
{
    updateTime();
}



void Tetris_Player::display()
{
    COUT << "Player stats :"<<ENDL;
    COUT << "--- Score : " << score << " pts" << ENDL;
    COUT << "--- Level : " << level << ENDL;
    COUT << "--- Time  : " << time << " s" << ENDL;
    COUT << "--- Speed : " << speed << ENDL;
    COUT << "--- Rows  : " << deletedRows << ENDL;
}

