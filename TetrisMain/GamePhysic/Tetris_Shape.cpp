#include "GamePhysic/Tetris_Shape.h"


Tetris_3DBloc::Tetris_3DBloc(Hakurei::Mesh *_bloc, Vec2f _pos) : Tetris_Bloc()
{
    bloc = _bloc;
    pos = _pos;

}





Tetris_Shape::Tetris_Shape(Uint8 blocType, Vec4f color)
{
    pos2D = Vec2f(0,0);
    pos3D = Vec3f(pos2D,0); // <--- use function to convert 2D pos to 3D Scene pos

    Hakurei::Mesh* tbloc = NULL;
    Hakurei::OpenScene* scene = getScene();
    switch(blocType)
    {
    case 0:
/* []
   [][]
     [] */

        // Up-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, color);
        blocs["SHAPE_0_UL"] = new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC/2, H_BLOC));
        // Middle-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, color);
        blocs["SHAPE_0_ML"] = new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC/2, 0));
        // Middle-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, color);
        blocs["SHAPE_0_MR"] = new Tetris_3DBloc(tbloc, Vec2f(W_BLOC/2, 0));
        // Down-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, color);
        blocs["SHAPE_0_DR"] = new Tetris_3DBloc(tbloc, Vec2f(W_BLOC/2, -H_BLOC));


        // CREATE ADD SHAPE TO SCENE FUNCTION
        typedef Map<String, Tetris_3DBloc*>::iterator it_bloc;
        for(it_bloc iterator = blocs.begin(); iterator != blocs.end(); iterator++)
        {
            scene->addObject(iterator->first, iterator->second->bloc);
        }


        break;


    }

}



void Tetris_Shape::drawShapeInScene(String matName)
{
    Hakurei::OpenScene* scene = getScene();
    Hakurei::Mesh* tbloc = NULL;
    Tetris_3DBloc* bloc3d = NULL;
    typedef Map<String, Tetris_3DBloc*>::iterator it_bloc;


    for(it_bloc iterator = blocs.begin(); iterator != blocs.end(); iterator++)
    {
        tbloc = scene->getObjectByName(iterator->first);
        bloc3d = iterator->second;
        tbloc->transform(TRANSFORM_TRANSLATION, SET_TRANSFORM, Vec3f(pos2D + bloc3d->pos, 0));
        scene->drawObjectInScene(iterator->first, matName);
    }
}
