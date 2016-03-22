#ifndef __TETRIS__SHAPE__
#define __TETRIS__SHAPE__

#include "lib/all.h"
#include "GameLogic/include/Tetris_Bloc.h"




#define W_BLOC      0.5
#define H_BLOC      0.5
#define D_BLOC      0.5


class Tetris_3DBloc : public Tetris_Bloc
{
public:
    Hakurei::Mesh* bloc;
    Vec2f pos; // position 2D relative to shape gravity center

    Tetris_3DBloc(Hakurei::Mesh* _bloc, Vec2f _pos);

};



class Tetris_Shape
{
public:
    Map<String, Tetris_3DBloc*> blocs;
    Vec3f pos3D;
    Vec2f pos2D;
    Uint8 type;



    Tetris_Shape(Uint8 blocType, Vec4f color);
    void drawShapeInScene(String matName);

};






#endif
