#ifndef __TETRIS__PHYSIC__
#define __TETRIS__PHYSIC__

#include "lib/all.h"
#include "GamePhysic/Tetris_Shape.h"
#include "GamePhysic/Tetris_3DBloc.h"
#include "GameLogic/Tetris_Matrix.h"
#include "GameLogic/Tetris_Player.h"

#define COLLISION_BOX               0.50

#define MOVE_RIGHT(shape)           moveShape(shape, Vec2f(0.333, 0.0))
#define MOVE_LEFT(shape)            moveShape(shape, Vec2f(-0.333, 0.0))
#define CANCEL_RIGHT(shape)         MOVE_LEFT(shape)
#define CANCEL_LEFT(shape)          MOVE_RIGHT(shape)



Bool blocCollision(Tetris_3DBloc* bloc, Vec2f gravityCenter, Tetris_Matrix* matrix, Bool fall);
Bool checkCollision(Tetris_Shape* shape, Tetris_Matrix* matrix, Bool fall);

void TetrisCameraUpdate(float shapeAngle);
//void RotateFix(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated);
void moveShape(Tetris_Shape* shape, Vec2f movement);
void updateGame(Tetris_Player* player);


#endif // __TETRIS__PHYSIC__
