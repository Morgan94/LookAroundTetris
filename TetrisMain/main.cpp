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


    shape = new Tetris_Shape(1);


    Hakurei::Mesh* center = new Hakurei::Mesh();
    center->createCube(2.0,2.0,2.0,Vec4f(1,1,1,1));
    scene->addObject("center",center);



    scene->camera->callbacks[GLFW_KEY_RIGHT] = NULL;
    scene->camera->callbacks[GLFW_KEY_LEFT] = NULL;
    scene->camera->callbacks[GLFW_KEY_UP] = NULL;
    scene->camera->callbacks[GLFW_KEY_DOWN] = NULL;



    return;
}


void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    enableThings();


    scene->drawObjectInScene("center","mat");

    shape->drawShapeInScene("mat");



    disableThings();
    return;
}


void mainLoop(void)
{
    do
    {
        updateStuff();
        // Rendering
        drawScene();
        swapBuffers();


        if(KEY_PRESSED(GLFW_KEY_RIGHT))
            shape->pos2D += Vec2f(0.1,0.0);
        if(KEY_PRESSED(GLFW_KEY_LEFT))
            shape->pos2D -= Vec2f(0.1,0.0);
        if(KEY_PRESSED(GLFW_KEY_UP))
            shape->pos2D += Vec2f(0.0,0.1);
        if(KEY_PRESSED(GLFW_KEY_DOWN))
            shape->pos2D -= Vec2f(0.0,0.1);



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
