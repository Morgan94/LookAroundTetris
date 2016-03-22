#include "lib/all.h"
#include "GameLogic/include/Tetris_Bloc.h"
#include "GameLogic/include/Tetris_Matrice.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "GamePhysic/Tetris_Shape.h"


Tetris_Shape* shape = NULL;



void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat",mat1);


    shape = new Tetris_Shape(0,Vec4f(1.0,0.0,0.0,1.0));


    return;
}


void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    scene->initDrawingScene();
    enableThings();


    shape->drawShapeInScene("mat");



    disableThings();
    return;
}


void mainLoop(void)
{
    do
    {
        // Rendering
        drawScene();
        swapBuffers();
        updateStuff();
    }
    while(!KEY_PRESSED(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(glfwGetCurrentContext()) == 0);

}


int main(int argc, char* argv[])
{
    GL_Initialization();
    make_resources();
    mainLoop();
    shutDown(0);
}
