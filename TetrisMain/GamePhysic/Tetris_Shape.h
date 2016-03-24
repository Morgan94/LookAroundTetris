#ifndef __TETRIS__SHAPE__
#define __TETRIS__SHAPE__

#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"





class Tetris_Shape
{
public:
    Vector<Tetris_3DBloc*> blocs;
    Vec2f pos2D; // position of gravity center
    Uint8 type; // shape type



    Tetris_Shape(Uint8 shapeType, Vec2f initialPos = Vec2f(0,0));
    void drawShapeInScene(String matName);

};






#endif
