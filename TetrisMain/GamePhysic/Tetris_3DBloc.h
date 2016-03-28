#ifndef __TETRIS__3DBLOC__
#define __TETRIS__3DBLOC__

#include "lib/all.h"


#define W_BLOC      1.00
#define H_BLOC      1.00
#define D_BLOC      0.30

#define R_CYL       (24.0 / (2.0*PI))

#define RED Vec4f(1,0,0,1)
#define PURPLE Vec4f(0.5,0,1,1)
#define GREEN Vec4f(0,1,0,1)
#define YELLOW Vec4f(1,1,0,1)
#define BLEU Vec4f(0,0,1,1)
#define ORANGE Vec4f(1,0.6,0,1)
#define CYAN Vec4f(0,1,1,1)


class Tetris_3DBloc
{
public:
    String blocName;
    Hakurei::Mesh* bloc;
    Vec2f pos2D; // position 2D relative to shape gravity center
    // auto update
    Vec2f truePos;
    Vec3f pos3D;
    float theta;
    // Matrix attrs
    Sint32 matX;
    Sint32 matY;


    Tetris_3DBloc(Hakurei::Mesh* _bloc, Vec2f _pos, String _blocName);
    void compute3DPos(Vec2f gravityCenter);
    void drawBlocInScene(String matName, Vec2f gravityCenter);
    void toMatrixCoords(Vec2f gravityCenter);

};





#endif
