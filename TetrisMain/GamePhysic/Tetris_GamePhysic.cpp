#include "GamePhysic/Tetris_GamePhysic.h"



Bool blocCollision(Tetris_3DBloc* bloc, Vec2f gravityCenter, Tetris_Matrix* matrix, Bool fall)
{
    bloc->compute2DPos(gravityCenter);
    Sint32 X = fixedMod((Sint32)(bloc->pos2D[0]), MATRIX_WIDTH);
    Sint32 Y;
    if(!fall) Y = (Sint32)(bloc->pos2D[1] + COLLISION_BOX);
    else Y = (Sint32)(bloc->pos2D[1]);

    if(bloc->pos2D[1] < 0 || matrix->get(X,Y) != NULL)
        return true;
    return false;
}


Bool checkCollision(Tetris_Shape* shape, Tetris_Matrix* matrix, Bool fall)
{
    Bool collision = 0;

    for(Uint32 b = 0; b < shape->blocs.size(); b++)
    {
        collision = blocCollision(shape->blocs[b], shape->pos2D, matrix, fall);
        if(collision) break;
    }
    return collision;
}

Uint32 RandomGen()
{
    Uint32 blocType = rand() % 7;
    return blocType;
}



// Key Callback //
float rota = 0;
void RotateFix(Hakurei::OpenCamera* camera, float deltaTime, Bool* rotated)
{
    camera->angleH = rota - PI/2;
    *rotated = true;
}
// ------------ //


// Shape updating //

void moveShape(Tetris_Shape* shape, Vec2f movement)
{
    shape->pos2D += movement;
    while(shape->pos2D[0] < FL_COLS) shape->pos2D[0] += FL_COLS;
    while(shape->pos2D[0] >= 2*FL_COLS) shape->pos2D[0] -= FL_COLS;
}

void updateGame(Tetris_Shape* shape, Tetris_Matrix* matrix, Tetris_Player* player)
{
    if(KEY_PRESSED(GLFW_KEY_RIGHT))
    {
        MOVE_RIGHT(shape);
        if(checkCollision(shape, matrix, false)) {CANCEL_RIGHT(shape);}
    }
    else if(KEY_PRESSED(GLFW_KEY_LEFT))
    {
        MOVE_LEFT(shape);
        if(checkCollision(shape, matrix, false)) {CANCEL_LEFT(shape);}
    }
    else if(KEY_PRESSED(GLFW_KEY_DOWN))
    {
       shape->pos2D -= Vec2f(0.0,10*player->getSpeed());
       player->incrementScore();
    }
    if(KEY_PRESSED(GLFW_KEY_SPACE))
    {
       shape->rotate90;
       if(checkCollision(shape,matrix,false))
           shape->rotate270;
    }

    shape->pos2D -= Vec2f(0.0,player->getSpeed());
    if(checkCollision(shape, matrix, true))
    {
        float lastPos = shape->pos2D[0];
        shape->pos2D += Vec2f(0.0, 0.6);
        matrix->addShapeToMatrix(shape);
        shape = new Tetris_Shape(RandomGen(), Vec2f(lastPos,MATRIX_HEIGHT));



        Uint32 count = 0;
        Sint32 row = 0;
        while((row = matrix->fullRow()) != -1)
        {
            // animation trop swag de destruction des blocs
            matrix->deleteRow(row);
            count++;

        }
        player->udpate_Player(count);

        player->display();
    }
    rota = ((2 * PI * (float)((Uint32)(shape->pos2D[0]))) / FL_COLS);
}

// --------------------- //
