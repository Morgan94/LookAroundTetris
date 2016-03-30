#include "GamePhysic/Tetris_Shape.h"


// ------ TETRIMINOS ------------ //
// TETRIMINO_BLOCS[ NUMBER, BLOC ]
const Vec2f TETRIMINO_BLOCS[7][4] = {
{Vec2f(-1, 1), Vec2f(0, 1), Vec2f(0, 0), Vec2f(1, 0)},
{Vec2f(0, 1), Vec2f(-1, 0), Vec2f(0, 0), Vec2f(1, 0)},
{Vec2f(-1, 0), Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1)},
{Vec2f(-0.5, 0.5), Vec2f(0.5, 0.5), Vec2f(0.5, -0.5), Vec2f(-0.5, -0.5)},
{Vec2f(-1, 0), Vec2f(0, 0), Vec2f(1, 0), Vec2f(1, 1)},
{Vec2f(-1, 1), Vec2f(-1, 0), Vec2f(0, 0), Vec2f(1, 0)},
{Vec2f(-1.5, 0.5), Vec2f(-0.5, 0.5), Vec2f(0.5, 0.5), Vec2f(1.5, 0.5)}
};

const Vec4f TETRIMINO_COLORS[7] = {
Vec4f(1, 0, 0, 1),
Vec4f(0.5, 0, 1, 1),
Vec4f(0, 1, 0, 1),
Vec4f(1, 1, 0, 1),
Vec4f(1, 0.5, 0, 1),
Vec4f(0, 0, 1, 1),
Vec4f(0, 1, 1, 1)
};



Tetris_Shape::Tetris_Shape(Uint8 shapeType, Vec2f initialPos)
{
    pos2D = initialPos;
    type = shapeType;
    blocs.clear();

    Vec2f v;
    if(shapeType < 7)
    {
        for(Uint32 b=0; b<4; b++)
        {
            v = TETRIMINO_BLOCS[type][b];
            v[0] *= W_BLOC;
            v[1] *= H_BLOC;
            blocs.push_back(ShapeBloc(v, TETRIMINO_COLORS[type]));
        }
    }
    else
    {
        for(int i=0; i<24; i++)
        {
            Hakurei::Mesh* tbloc = new Hakurei::Mesh();
            tbloc->createCube(0.2, H_BLOC, D_BLOC*1.2,Vec4f(1,1,1,1));
            blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(i*W_BLOC, -0.55)));
        }
    }

}


Tetris_3DBloc* Tetris_Shape::ShapeBloc(Vec2f position, Vec4f color)
{
    Hakurei::Mesh* tbloc = new Hakurei::Mesh();
    tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, color);
    return (new Tetris_3DBloc(tbloc, position));
}



void Tetris_Shape::drawShapeInScene(String matName)
{
    Tetris_3DBloc* bloc3d = NULL;
    for(Uint32 i=0; i<blocs.size(); i++)
    {
        bloc3d = blocs[i];
        bloc3d->drawBlocInScene(matName, pos2D);
    }
}



void Tetris_Shape::rotate(Uint32 n)
{
    Tetris_3DBloc* bloc3d = NULL;
    n = n%4;
    while(n > 0)
    {
        n--;
        for(Uint32 i=0; i<blocs.size(); i++)
        {
            bloc3d = blocs[i];
            bloc3d->localPos = Vec2f(bloc3d->localPos[1], -bloc3d->localPos[0]);
        }
    }
}

