#include "GamePhysic/Tetris_3DBloc.h"


Tetris_3DBloc::Tetris_3DBloc(Hakurei::Mesh* _bloc, Vec2f _pos, String _blocName)
{
    bloc = _bloc;
    pos2D = _pos;
    blocName = _blocName;
}

void Tetris_3DBloc::compute3DPos(Vec2f gravityCenter)
{
    truePos = pos2D + gravityCenter;
    theta = (2 * PI * truePos[0]) / 24;

    pos3D[0] = cos(theta) * R_CYL;
    pos3D[1] = truePos[1];
    pos3D[2] = -sin(theta) * R_CYL;
}


void Tetris_3DBloc::drawBlocInScene(String matName, Vec2f gravityCenter)
{
    Hakurei::OpenScene* scene = getScene();

    if(scene->getObjectByName(blocName) == NULL)
        scene->addObject(blocName, bloc);

    compute3DPos(gravityCenter);
    bloc->transform(TRANSFORM_TRANSLATION, SET_TRANSFORM, pos3D);
    bloc->transform(TRANSFORM_ROTATION, SET_TRANSFORM, Vec3f(0,1,0), (2 * PI * truePos[0]) / 24);
    scene->drawObjectInScene(blocName, matName);
}


void Tetris_3DBloc::toMatrixCoords(Vec2f gravityCenter)
{
    truePos = pos2D + gravityCenter;
    matX = ((Sint32)(truePos[0]))%24;
    while(matX < 0) matX += 24;
    matY = (Sint32)(truePos[1]);
}

