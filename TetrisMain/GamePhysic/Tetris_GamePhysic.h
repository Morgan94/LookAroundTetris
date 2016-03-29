#ifndef __TETRIS__PHYSIC__
#define __TETRIS__PHYSIC__

#include "lib/all.h"
#include "GamePhysic/Tetris_Shape.h"
#include "GamePhysic/Tetris_3DBloc.h"
#include "GameLogic/Tetris_Matrix.h"

#define COLLISION_SIDE          1
#define COLLISION_DOWN          2
#define COLLISION_BOX           0.50

Bool blocCollision(Tetris_3DBloc* bloc, Vec2f gravityCenter, Tetris_Matrix* matrix, Bool fall);
Bool checkCollision(Tetris_Shape* shape, Tetris_Matrix* matrix, Bool fall);
Uint32 RandomGen();


#endif // __TETRIS__PHYSIC__
