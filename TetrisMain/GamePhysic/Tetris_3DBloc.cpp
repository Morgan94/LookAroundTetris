#include "GamePhysic/Tetris_3DBloc.h"


Tetris_3DBloc::Tetris_3DBloc(Hakurei::Mesh* _bloc, Vec2f _pos, Uint32 _value)
{
    static Uint32 blocNumber = 0;
    bloc = _bloc;
    localPos = _pos;
    value = _value;
    char newBlocName[16];
    sprintf(newBlocName, "BLOC_%u", blocNumber);
    blocName = String(newBlocName);
    blocNumber++;
}


void Tetris_3DBloc::compute2DPos(Vec2f gravityCenter)
{
    pos2D = localPos + gravityCenter;
}


void Tetris_3DBloc::drawBlocInScene(String matName, Vec2f gravityCenter)
{
    Hakurei::OpenScene* scene = getScene();

    if(scene->getObjectByName(blocName) == NULL)
        scene->addObject(blocName, bloc);

    compute2DPos(gravityCenter);
    bloc->transform(TRANSFORM_ROTATION, SET_TRANSFORM, Vec3f(0, 1, 0), ((2 * PI * (float)((Sint32)pos2D[0])) / FL_COLS));
    bloc->transform(TRANSFORM_TRANSLATION, SET_TRANSFORM, Vec3f(R_CYL, pos2D[1], 0));
    scene->drawObjectInScene(blocName, matName);
}


void Tetris_3DBloc::deleteBloc()
{
    Hakurei::OpenScene* scene = getScene();

    if(scene->getObjectByName(blocName) == NULL)
        scene->removeObject(blocName);
}

