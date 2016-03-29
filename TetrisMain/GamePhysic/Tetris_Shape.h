#ifndef __TETRIS__SHAPE__
#define __TETRIS__SHAPE__

#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"


enum {TETRIMINO_Z, TETRIMINO_T, TETRIMINO_S, TETRIMINO_O, TETRIMINO_L, TETRIMINO_J, TETRIMINO_I};


class Tetris_Shape
{
public:
    Vector<Tetris_3DBloc*> blocs;
    Vec2f pos2D; // position of gravity center
    Uint8 type; // shape type
    Uint8 rotation;




    Tetris_Shape(Uint8 shapeType, Vec2f initialPos = Vec2f(0,0));
    void drawShapeInScene(String matName);

private:
    Tetris_3DBloc* ShapeBloc(Vec2f position, Vec4f color);

};






#endif
