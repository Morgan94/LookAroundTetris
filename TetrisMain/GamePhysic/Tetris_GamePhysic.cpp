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








// Replace standard camera updating
void TetrisCameraUpdate(float shapeAngle)
{
	Hakurei::OpenCamera* camera = getScene()->camera;
    camera->computeCameraMark();
    Vec3f oldDirection = camera->direction;

	camera->angleH = shapeAngle - PI/2;
    camera->computeCameraMark();
    Vec3f distCamCenter = camera->position - camera->cameraTarget;
    double distance = sqrt(distCamCenter[0] * distCamCenter[0] + distCamCenter[2] * distCamCenter[2]);
    camera->position += Vec3f(oldDirection - camera->direction) * (float)(distance);

	getScene()->updateCamera();

	return;
}





// Shape updating //

void moveShape(Tetris_Shape* shape, Vec2f movement)
{
    shape->pos2D += movement;
    while(shape->pos2D[0] < FL_COLS) shape->pos2D[0] += FL_COLS;
    while(shape->pos2D[0] >= 2*FL_COLS) shape->pos2D[0] -= FL_COLS;
}

void line_music();
void updateGame(Tetris_Player* player)
{
    if(KEY_PRESSED(GLFW_KEY_RIGHT))
    {
        MOVE_RIGHT(player->shape);
        if(checkCollision(player->shape, player->matrix, false)) {CANCEL_RIGHT(player->shape);}
    }
    else if(KEY_PRESSED(GLFW_KEY_LEFT))
    {
        MOVE_LEFT(player->shape);
        if(checkCollision(player->shape, player->matrix, false)) {CANCEL_LEFT(player->shape);}
    }

    if(KEY_PRESSED(GLFW_KEY_SPACE) || KEY_PRESSED(GLFW_KEY_UP))
    {
        player->shape->rotate90;
        if(checkCollision(player->shape, player->matrix, false))
            player->shape->rotate270;
    }

    if(KEY_PRESSED(GLFW_KEY_DOWN))
    {
        player->shape->pos2D -= Vec2f(0.0, 0.5);
        player->incrementScore();
    }
    else
    {
        player->shape->pos2D -= Vec2f(0.0, 2 * player->speed);
    }

    if(checkCollision(player->shape, player->matrix, true))
    {
        float lastPos = player->shape->pos2D[0];
        player->shape->pos2D += Vec2f(0.0, 0.9);
        player->matrix->addShapeToMatrix(player->shape);

        player->shape = new Tetris_Shape(player->nextShapeT, Vec2f(lastPos, FL_ROWS));
        player->nextShapeT = RandomGen();

        player->scene->removeObject("next_shape");
        player->nextShape = new Hakurei::Mesh();
        createNextShapeObject(player->nextShape, player->nextShapeT);
        player->scene->addObject("next_shape", player->nextShape);

        Vector<Uint32> delRows;
        delRows.clear();
        for(Uint32 y=0; y<MATRIX_HEIGHT; y++)
            if(player->matrix->rowFull(y)) delRows.push_back(y);
        if(delRows.size() > 0)
        {
            line_music();
            float t = glfwGetTime();
            do
            {
                float newAlpha = 1.0 - (glfwGetTime() - t);
                if(newAlpha < 0.0) newAlpha = 0.0;
                for(Uint32 y : delRows)
                {
                    for(Uint32 x = 0; x < MATRIX_WIDTH; x++)
                        player->matrix->get(x,y)->alpha = newAlpha;
                }
                FrameRate(30);
                player->scene->initDrawingScene();
                enableThings();
                player->shape->drawShapeInScene("bloc");
                player->matrix->drawMatrixInScene("bloc");
                player->socle->drawShapeInScene("mat");
                if(player->displaySupport) player->scene->drawObjectInScene("cylinder", "mat");
                player->scene->drawObjectInScene("next_shape", "next");
                disableThings();
                swapBuffers();
            }
            while(glfwGetTime() - t < 1.0);

            Sint32 row;
            while((row = player->matrix->fullRow()) != -1)
                player->matrix->deleteRow(row);
            player->updateScore(delRows.size());
        }
        player->display();
    }

    TetrisCameraUpdate(((2 * PI * (float)((Uint32)(player->shape->pos2D[0]))) / FL_COLS));
}

// --------------------- //

