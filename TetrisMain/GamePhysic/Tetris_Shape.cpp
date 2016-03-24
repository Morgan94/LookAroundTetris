#include "GamePhysic/Tetris_Shape.h"




Tetris_Shape::Tetris_Shape(Uint8 shapeType, Vec2f initialPos)
{
    pos2D = initialPos;
    blocs.clear();

    Hakurei::Mesh* tbloc = NULL;
    switch(shapeType)
    {
    case 0:
/* [][]
     [][] */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(1,0,0,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, H_BLOC), "SHAPE0_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(1,0,0,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE0_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(1,0,0,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE0_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(1,0,0,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, 0), "SHAPE0_3"));
        break;

    case 1:
/*   []
   [][][] */
        // Up-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(0.5,0,1,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE1_0"));
        // Middle-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(0.5,0,1,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE1_1"));
        // Middle-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(0.5,0,1,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, 0), "SHAPE1_2"));
        // Down-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, Vec4f(0.5,0,1,1));
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE1_3"));
        break;


    }

    type = shapeType;

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
