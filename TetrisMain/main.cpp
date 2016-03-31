#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"
#include "GameLogic/Tetris_Matrix.h"
#include "GameLogic/Tetris_Player.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "GamePhysic/Tetris_Shape.h"




Tetris_Shape* shape = NULL;
Tetris_Shape* nextShape = NULL;
Uint8 nextShapeT = 0;
Tetris_Shape* socle = NULL;
Tetris_Matrix* matrix = NULL;
Tetris_Player* player = NULL;
Bool displaySupport = true;


void init_Player(){

    player = new Tetris_Player();
    player->startTime();

}

void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("cylinder.v.glsl","cylinder.f.glsl");
    scene->addMaterial("mat",mat1);

    Hakurei::Material* mat2 = new Hakurei::Material("light.v.glsl","light.f.glsl");
    mat2->addTexture(new Hakurei::Texture("tetris_colors_64.tga"));
    scene->addMaterial("text",mat2);

    Hakurei::Material* mat3 = new Hakurei::Material("next_tetris_bloc.v.glsl","next_tetris_bloc.f.glsl");
    scene->addMaterial("next",mat3);

    Hakurei::Mesh* cylinder = new Hakurei::Mesh();
    cylinder->createCylinder(R_CYL, FL_ROWS, MATRIX_WIDTH, MATRIX_HEIGHT, Vec4f(1,1,1,1), true);
    scene->addObject("cylinder", cylinder);

    setCallback(GLFW_KEY_LEFT, &RotateFix);
    setCallback(GLFW_KEY_RIGHT, &RotateFix);
    unsetCallback(GLFW_KEY_UP);
    unsetCallback(GLFW_KEY_DOWN);
    unsetCallback(GLFW_KEY_Q);



    matrix = new Tetris_Matrix();


    socle = new Tetris_Shape(7);
    shape = new Tetris_Shape(RandomGen(),Vec2f(6,FL_ROWS));
    nextShapeT = RandomGen();
    nextShape = new Tetris_Shape(nextShapeT);



    scene->kh->disableKeyRepeat(GLFW_KEY_SPACE);
    scene->kh->disableKeyRepeat(GLFW_KEY_Q);


    player = new Tetris_Player();

    return;
}


void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    enableThings();





    shape->drawShapeInScene("text");
    matrix->drawMatrixInScene("text");


    socle->drawShapeInScene("mat");
    if(displaySupport) scene->drawObjectInScene("cylinder", "mat");


    //nextShape->drawShapeInScene("next");


    disableThings();
    return;
}


void mainLoop(void)
{
    do
    {
        if(matrix->defeat())
        {
            std::cout << "SCORE FINAL"<<std::endl;
            player->display();
            break;
        }
        else
        {
            updateGame(shape, &nextShapeT, matrix, player);

            updateStuff();
            player->udpatePlayer();
            drawScene();
            swapBuffers();


            if(KEY_PRESSED(GLFW_KEY_Q))
            {
                if(displaySupport) displaySupport = false;
                else displaySupport = true;
            }
        }
    }
    while(!KEY_PRESSED(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(glfwGetCurrentContext()) == 0);

}


int main(int argc, char* argv[])
{
    srand(time(NULL));
    GL_Initialization();
    make_resources();
    init_Player();
    mainLoop();
    shutDown(0);
}

