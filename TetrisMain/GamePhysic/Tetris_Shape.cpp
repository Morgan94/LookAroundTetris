#include "GamePhysic/Tetris_Shape.h"




Tetris_Shape::Tetris_Shape(Uint8 shapeType, Vec2f initialPos)
{
    pos2D = initialPos;
    blocs.clear();

    Hakurei::Mesh* tbloc = NULL;
    switch(shapeType)
    {
    case 0:
/* [][]    //Red
     [][] */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, RED);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, H_BLOC), "SHAPE0_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, RED);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE0_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, RED);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE0_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, RED);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, 0), "SHAPE0_3"));
        break;

    case 1:
/*   []    //Purple
   [][][] */
        // Up-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, PURPLE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE1_0"));
        // Middle-left bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, PURPLE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE1_1"));
        // Middle-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, PURPLE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, 0), "SHAPE1_2"));
        // Down-right bloc
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, PURPLE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE1_3"));
        break;

    case 2:
/*  [][]   //Green
  [][]    */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, GREEN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, H_BLOC), "SHAPE2_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, GREEN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE2_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, GREEN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE2_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, GREEN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE2_3"));
        break;

    case 3:
/* [][]   //Yellow
   [][]  */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, YELLOW);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, H_BLOC), "SHAPE3_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, YELLOW);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, H_BLOC), "SHAPE3_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, YELLOW);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE3_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, YELLOW);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE3_3"));
        break;

    case 4:
/* []      //Bleu
   [][][] */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, BLEU);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, H_BLOC), "SHAPE4_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, BLEU);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, 0), "SHAPE4_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, BLEU);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE4_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, BLEU);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE4_3"));
        break;

    case 5:
 /*     []   //Orange
    [][][]  */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, ORANGE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC, H_BLOC), "SHAPE5_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, ORANGE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC,0), "SHAPE5_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, ORANGE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE5_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, ORANGE);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE5_3"));
        break;

    case 6:
 /*  [][][][] //Cyan
             */
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, CYAN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(2*W_BLOC, 0), "SHAPE6_0"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, CYAN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(W_BLOC,0), "SHAPE6_1"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, CYAN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(0, 0), "SHAPE6_2"));
        tbloc = new Hakurei::Mesh();
        tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, CYAN);
        blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(-W_BLOC, 0), "SHAPE6_3"));
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
