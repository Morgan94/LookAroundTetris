#include "lib/all.h"
#include "GamePhysic/Tetris_3DBloc.h"
#include "GameLogic/Tetris_Matrix.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "GamePhysic/Tetris_Shape.h"


Tetris_Shape* shape = NULL;
Tetris_Shape* socle = NULL;
Tetris_Matrix* matrix = NULL;


Sint32 rota = 0;


void RotateLeft2(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{

        camera->angleH -= 2 * PI * 0.2 / 24;
        *rotated = true;


}

void RotateRight2(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{

        camera->angleH += 2 * PI * 0.2 / 24;
        *rotated = true;

}






void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat",mat1);


    shape = new Tetris_Shape(RandomGen(),Vec2f(6,10));


    Hakurei::Mesh* center = new Hakurei::Mesh();
    center->createCube(2.0,2.0,2.0,Vec4f(1,1,1,1));
    scene->addObject("center",center);


    unsetCallback(GLFW_KEY_LEFT);
    unsetCallback(GLFW_KEY_RIGHT);
    unsetCallback(GLFW_KEY_UP);
    unsetCallback(GLFW_KEY_DOWN);

    matrix = new Tetris_Matrix();

    Hakurei::Mesh* tbloc;




    socle = new Tetris_Shape(7);





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
    Uint32 oldX;

    do
    {
        updateStuff();
        // Rendering
        drawScene();
        swapBuffers();



        if(KEY_PRESSED(GLFW_KEY_RIGHT))
        {
            shape->pos2D += Vec2f(0.2,0.0);
            if(checkCollision(shape, matrix, false))
                shape->pos2D -= Vec2f(0.2,0.0);
        }

        if(KEY_PRESSED(GLFW_KEY_LEFT))
        {
            shape->pos2D -= Vec2f(0.2,0.0);
            if(checkCollision(shape, matrix, false))
                shape->pos2D += Vec2f(0.2,0.0);
        }

        if(KEY_PRESSED(GLFW_KEY_UP))
            shape->pos2D += Vec2f(0.0,0.1);

        if(1)
        {

            shape->pos2D -= Vec2f(0.0, 0.05);
            if(checkCollision(shape, matrix, true))
            {
                float lastPos = shape->pos2D[0];
                shape->pos2D += Vec2f(0.0, 0.6);
                matrix->addShapeToMatrix(shape);
                shape = new Tetris_Shape(RandomGen(), Vec2f(lastPos,15));

                Uint32 row;
                while((row = matrix->fullRow()) != -1)
                {
                    // animation trop swag de destruction des blocs
                    matrix->deleteRow(row);
                }
                matrix->display();
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
    mainLoop();
    shutDown(0);
}
