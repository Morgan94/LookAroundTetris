#include "GamePhysic/Tetris_GamePhysic.h"



Bool blocCollision(Tetris_3DBloc* bloc, Vec2f gravityCenter, Tetris_Matrix* matrix, Bool fall)
{
    bloc->compute2DPos(gravityCenter);
    Sint32 X = fixedMod((Sint32)(bloc->pos2D[0]), 24);
    Sint32 Y;
    if(!fall) Y = (Sint32)(bloc->pos2D[1] + COLLISION_BOX);
    else Y = (Sint32)(bloc->pos2D[1]);

    if(bloc->pos2D[1] < 0 || matrix->get(X,Y) != NULL)
        return true;
    return false;
}


Bool checkCollision(Tetris_Shape* shape, Tetris_Matrix* matrix, Bool fall)
{
    Bool collision = 0;

    for(Uint32 b = 0; b < shape->blocs.size(); b++)
    {
        collision = blocCollision(shape->blocs[b], shape->pos2D, matrix, fall);
        if(collision) break;
    }
    return collision;
}

Uint32 RandomGen()
{
    Uint32 blocType = rand() % 7;
    return blocType;
}
