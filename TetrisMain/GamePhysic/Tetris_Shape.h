#ifndef __TETRIS__SHAPE__
#define __TETRIS__SHAPE__

#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"


enum {TETRIMINO_Z, TETRIMINO_T, TETRIMINO_S, TETRIMINO_O, TETRIMINO_L, TETRIMINO_J, TETRIMINO_I};
#define rotate90                rotate(1)
#define rotate180               rotate(2)
#define rotate270               rotate(3) // = rotate -90°



class Tetris_Shape
{
public:
    Vector<Tetris_3DBloc*> blocs;
    Vec2f pos2D; // position of gravity center
    Uint8 type; // shape type



    Tetris_Shape(Uint8 shapeType, Vec2f initialPos = Vec2f(0,0));
    void drawShapeInScene(String matName);
    void rotate(Uint32 n = 1); // rotate +90° x n

private:
    Tetris_3DBloc* ShapeBloc(Vec2f position, Vec4f color);

};






#endif
