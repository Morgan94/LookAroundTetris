#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"
#include "GameLogic/Tetris_Matrix.h"
#include "GameLogic/Tetris_Player.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "GamePhysic/Tetris_Shape.h"


Tetris_Shape* shape = NULL;
Tetris_Shape* socle = NULL;
Tetris_Matrix* matrix = NULL;
Tetris_Player* player= NULL;

void init_Player(){

    player = new Tetris_Player();
    player->startTime();

}

void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat",mat1);


    shape = new Tetris_Shape(RandomGen(),Vec2f(6,MATRIX_HEIGHT));


    Hakurei::Mesh* center = new Hakurei::Mesh();
    center->createCube(2.0,2.0,2.0,Vec4f(1,1,1,1));
    scene->addObject("center",center);


    setCallback(GLFW_KEY_LEFT, &RotateFix);
    setCallback(GLFW_KEY_RIGHT, &RotateFix);
    unsetCallback(GLFW_KEY_UP);
    unsetCallback(GLFW_KEY_DOWN);

    matrix = new Tetris_Matrix();


    socle = new Tetris_Shape(7);

    scene->kh->disableKeyRepeat(GLFW_KEY_SPACE);

    return;
}


void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    enableThings();


    scene->drawObjectInScene("center","mat");

    socle->drawShapeInScene("mat");

    shape->drawShapeInScene("mat");



    matrix->drawMatrixInScene("mat");



    disableThings();
    return;
}



void mainLoop(void)
{
    do
    {
        if(matrix->defeat()){
            std::cout << "SCORE FINAL"<<std::endl;
            player->display();
            break;

        }
        else{
            updateGame(shape, matrix,player);

            updateStuff();
            drawScene();
            swapBuffers();
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

