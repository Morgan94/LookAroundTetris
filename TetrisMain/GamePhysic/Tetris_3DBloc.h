#ifndef __TETRIS__3DBLOC__
#define __TETRIS__3DBLOC__

#include "lib/all.h"

#define W_BLOC      1.00
#define H_BLOC      1.00
#define D_BLOC      0.30

class Tetris_3DBloc
{
public:
    String blocName;
    Hakurei::Mesh* bloc;
    Vec2f localPos; // position 2D relative to shape gravity center
    // auto update
    Vec2f pos2D; // ~= Matrix position
    // Matrix attributes
    Uint32 value;


    Tetris_3DBloc(Hakurei::Mesh* _bloc, Vec2f _pos = Vec2f(0,0), Uint32 _value = 6);
    void compute2DPos(Vec2f gravityCenter);
    void drawBlocInScene(String matName, Vec2f gravityCenter);
    void deleteBloc();

};


#include "GameLogic/Tetris_Matrix.h"
#define FL_ROWS     ((float)(MATRIX_HEIGHT))
#define FL_COLS     ((float)(MATRIX_WIDTH))
#define R_CYL       (FL_COLS / (2.0*PI))




#endif
