#include "lib/all.h"
#include "GameLogic/Tetris_Bloc.h"
#include "GameLogic/Tetris_Matrix.h"
#include "GamePhysic/Tetris_GamePhysic.h"


void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat",mat1);

    Hakurei::Mesh* obj1 = new Hakurei::Mesh();
    obj1->importOBJ("base.obj");
    obj1->transform(TRANSFORM_SCALE, SET_TRANSFORM, Vec3f(0.1,0.1,0.1));
    obj1->transform(TRANSFORM_ALL, SET_TRANSFORM_AS_DEFAULT);
    scene->addObject("cylinder",obj1);


    return;
}


void drawScene()
{
    Hakurei::OpenScene* scene = getScene();

    scene->initDrawingScene();
    enableThings();


    scene->getMaterialByName("mat")->setAlpha(1);
    scene->drawObjectInScene("cylinder","mat");



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
