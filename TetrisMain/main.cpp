#include "lib/all.h"
#include "GameLogic/include/Tetris_Bloc.h"
#include "GameLogic/include/Tetris_Matrice.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "GamePhysic/Tetris_Shape.h"


Tetris_Shape* shape = NULL;
Tetris_Shape* shape2 = NULL;
Tetris_Matrice *tm = new Tetris_Matrice(width, height);

Tetris_Matrice* matrix_test(void)
{
    Tetris_Matrice *tm = new Tetris_Matrice(width, height);

        for(int j=0;j<22;j++)
        {
            (*tm)[0][j]->setCheck(true);
            (*tm)[0][j]->setColor(CYAN);
            (*tm)[1][j]->setCheck(true);
            (*tm)[0][j]->setColor(RED);
        }

        return tm;
}

void draw_matrix(Tetris_Matrice *tm,Vec2f initialPos)
{
    Vector<Tetris_3DBloc*> blocs;
    Hakurei::Mesh* tbloc = NULL;
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<24;j++)
        {
            if(!((*tm)[i][j]->isEmpty()))
            {
                int color = (*tm)[i][j]->getColor();
                tbloc = new Hakurei::Mesh();
                if(color = 1)
                    tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, C_CYAN);
                if(color = 7)
                    tbloc->createCube(W_BLOC, H_BLOC, D_BLOC, C_RED);
                String name="SHAPEM_0";

                blocs.push_back(new Tetris_3DBloc(tbloc, Vec2f(j*W_BLOC, i*H_BLOC), name));
            }
        }
    }
    Vec2f pos2D = initialPos;
    Tetris_3DBloc* bloc3d = NULL;

    for(Uint32 i=0; i<blocs.size(); i++)
    {
        bloc3d = blocs[i];
        bloc3d->drawBlocInScene("mat", pos2D);
    }
}

void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    Hakurei::Material* mat1 = new Hakurei::Material("simple.v.glsl","simple.f.glsl");
    scene->addMaterial("mat",mat1);


    tm = matrix_test();


    shape = new Tetris_Shape(1,Vec2f(0,20));
    shape2 = new Tetris_Shape(7);


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
    shape2->drawShapeInScene("mat");
    draw_matrix(tm,Vec2f(0,0));



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

        getScene()->kh->disableKeyRepeat(GLFW_KEY_RIGHT);
        getScene()->kh->disableKeyRepeat(GLFW_KEY_LEFT);
        if(KEY_PRESSED(GLFW_KEY_RIGHT))
            shape->pos2D += Vec2f(W_BLOC,0.0);
        if(KEY_PRESSED(GLFW_KEY_LEFT))
            shape->pos2D -= Vec2f(W_BLOC,0.0);
        if(KEY_PRESSED(GLFW_KEY_UP))
            shape->pos2D += Vec2f(0.0,0.1);
        if(KEY_PRESSED(GLFW_KEY_DOWN))
            if(shape->pos2D[1]>0.1)
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
