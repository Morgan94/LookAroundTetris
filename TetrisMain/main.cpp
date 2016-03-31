#include "lib/all.h"
#include "GameLogic/Tetris_Player.h"
#include "GamePhysic/Tetris_GamePhysic.h"
#include "irrKlang.h"


Tetris_Player* player = NULL;
Bool titleScreen = false;


using namespace irrklang;
ISoundEngine* SoundEngine = NULL;
void init_music()
{
    SoundEngine = createIrrKlangDevice();
    if(SoundEngine == NULL)
        exitOnError("Sound Engine not initialized correctly.");
    SoundEngine->play2D("../resources/audio/TetrisTheme_WAV.wav", GL_TRUE);
}

void end_music()
{
    SoundEngine->drop();
}



void make_resources(void)
{
    Hakurei::OpenScene* scene = getScene();

    if(titleScreen)
    {
        // Materials

        Hakurei::Material* mat0 = new Hakurei::Material("shaders/title.v.glsl", "shaders/title.f.glsl");
        mat0->addTexture(new Hakurei::Texture("textures/TitleScreen.tga"));
        scene->addMaterial("title_mat", mat0);


        // Objects

        Hakurei::Mesh* obj0 = new Hakurei::Mesh();
        obj0->vertices.clear();
        obj0->triangles.clear();
        obj0->vertices.push_back(Hakurei::Vertex(Vec3f(-1,1,0), Vec3f(), Vec3f(), Vec2f(0,1)));
        obj0->vertices.push_back(Hakurei::Vertex(Vec3f(1,1,0), Vec3f(), Vec3f(), Vec2f(1,1)));
        obj0->vertices.push_back(Hakurei::Vertex(Vec3f(1,-1,0), Vec3f(), Vec3f(), Vec2f(1,0)));
        obj0->vertices.push_back(Hakurei::Vertex(Vec3f(-1,-1,0), Vec3f(), Vec3f(), Vec2f(0,0)));
        obj0->triangles.push_back(Hakurei::Triangle(0,2,1));
        obj0->triangles.push_back(Hakurei::Triangle(0,3,2));
        obj0->computeNormals();
        scene->addObject("title_screen", obj0);
    }
    else
    {
        // Materials

        Hakurei::Material* mat1 = new Hakurei::Material("shaders/cylinder.v.glsl", "shaders/cylinder.f.glsl");
        scene->addMaterial("mat",mat1);

        Hakurei::Material* mat2 = new Hakurei::Material("shaders/light.v.glsl", "shaders/light.f.glsl");
        mat2->addTexture(new Hakurei::Texture("textures/tetris_colors_64.tga"));
        scene->addMaterial("bloc",mat2);

        Hakurei::Material* mat3 = new Hakurei::Material("shaders/next.v.glsl", "shaders/next.f.glsl");
        scene->addMaterial("next",mat3);


        // Objects

        Hakurei::Mesh* cylinder = new Hakurei::Mesh();
        cylinder->createCylinder(R_CYL, FL_ROWS, MATRIX_WIDTH, MATRIX_HEIGHT, Vec4f(1,1,1,1), true);
        scene->addObject("cylinder", cylinder);

        player = new Tetris_Player();
        player->matrix = new Tetris_Matrix();
        player->socle = new Tetris_Shape(7);
        player->shape = new Tetris_Shape(RandomGen(),Vec2f(6,FL_ROWS));
        player->nextShapeT = RandomGen();
        player->nextShape = new Hakurei::Mesh();
        createNextShapeObject(player->nextShape, player->nextShapeT);
        player->scene->addObject("next_shape", player->nextShape);
        player->scene->kh->disableKeyRepeat(GLFW_KEY_SPACE);
        player->scene->kh->disableKeyRepeat(GLFW_KEY_Q);
        player->scene->kh->disableKeyRepeat(GLFW_KEY_P);
        player->displaySupport = false;
    }
    return;
}


void drawScene()
{
    enableThings();
    if(titleScreen)
    {
        getScene()->drawObjectInScene("title_screen", "title_mat");
    }
    else
    {
        player->shape->drawShapeInScene("bloc");
        player->matrix->drawMatrixInScene("bloc");
        player->socle->drawShapeInScene("mat");
        if(player->displaySupport) player->scene->drawObjectInScene("cylinder", "mat");
        player->scene->drawObjectInScene("next_shape", "next");
    }
    disableThings();
    return;
}







void mainLoop(void)
{
    do
    {
        if(player->matrix->defeat())
        {
            COUT << "SCORE FINAL"<< ENDL;
            player->display();
            break;

        }
        else
        {
            updateGame(player);

            updateStuff();
            player->udpatePlayer();
            drawScene();
            swapBuffers();


            if(KEY_PRESSED(GLFW_KEY_Q))
            {
                if(player->displaySupport) player->displaySupport = false;
                else player->displaySupport = true;
            }
            if(KEY_PRESSED(GLFW_KEY_P))
            {
                // afficher message pause


                do
                {
                    usleep(100000);
                    KEY_UPDATE;
                }
                while(!KEY_PRESSED(GLFW_KEY_P));
            }
        }
    }
    while(!KEY_PRESSED(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(glfwGetCurrentContext()) == 0);
}



void TitleScreen()
{
    titleScreen = true;
    make_resources();
    drawScene();
    swapBuffers();

    getScene()->kh->key[GLFW_KEY_ENTER] = false;
    getScene()->kh->disableKeyRepeat(GLFW_KEY_ENTER);
    do
    {
        usleep(100000);
        KEY_UPDATE;
    }
    while(!KEY_PRESSED(GLFW_KEY_ENTER) && !KEY_PRESSED(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(glfwGetCurrentContext()) == 0);

    if(KEY_PRESSED(GLFW_KEY_ENTER)) titleScreen = false;
    return;
}




int main(int argc, char* argv[])
{
    srand(time(NULL));
    GL_Initialization();
    init_music();
    TitleScreen();
    if(!titleScreen)
    {
        make_resources();
        mainLoop();
    }
    end_music();
    shutDown(0);
}
