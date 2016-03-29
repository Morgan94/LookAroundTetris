#include "GameLogic/Tetris_Matrix.h"



Tetris_Matrix::Tetris_Matrix(Sint32 _width, Sint32 _height)
{
    if(_width <= 0 || _height <= 0)
        exitOnError("Cannot create Matrix with non-positive dimensions.");

    width = _width;
    height = _height;
    blocs = new Tetris_3DBloc*[width * height];
    memset(blocs, 0, sizeof(Tetris_3DBloc*) * width * height);
}

Tetris_3DBloc** Tetris_Matrix::operator[](Sint32 y)
{
    if(y < 0 || y >= height)
        return NULL;
    return &(blocs[y * width]);
}



Tetris_3DBloc** Tetris_Matrix::at(Sint32 x, Sint32 y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return NULL;
    return &(blocs[y * width + x]);
}

Tetris_3DBloc* Tetris_Matrix::get(Sint32 x, Sint32 y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return NULL;
    return *at(x,y);
}

void Tetris_Matrix::set(Sint32 x, Sint32 y, Tetris_3DBloc* bloc)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return;
    *at(x,y) = bloc;
}



void Tetris_Matrix::addShapeToMatrix(Tetris_Shape* shape)
{
    Tetris_3DBloc* bloc;
    Sint32 Xmat, Ymat;
    for(Uint32 b = 0; b < shape->blocs.size(); b++)
    {
        bloc = shape->blocs[b];
        bloc->compute2DPos(shape->pos2D);
        Xmat = fixedMod((Sint32)(bloc->pos2D[0]), MATRIX_WIDTH);
        Ymat = (Sint32)(bloc->pos2D[1]);
        // add to Matrix
        bloc->localPos = Vec2f(0,0);
        set(Xmat, Ymat, bloc);
    }
    delete shape;
}



void Tetris_Matrix::removeBloc(Sint32 x, Sint32 y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
        return;

    Hakurei::OpenScene* scene = getScene();
    Tetris_3DBloc* bloc = get(x,y);
    bloc->deleteBloc();
    delete bloc;
    set(x, y, NULL);
}

void Tetris_Matrix::deleteRow(Sint32 y)
{
    if(y < 0 || y >= height)
        return;

    // delete physical objects
    for(Sint32 x = 0; x < width; x++)
        removeBloc(x, y);

    // lower rows above
    memcpy(at(0, y), at(0, y+1), sizeof(Tetris_3DBloc*) * width * (height - y - 1)); // faster than memmove (?)
    memset(at(0, height-1), 0, sizeof(Tetris_3DBloc*) * width);
}

Sint32 Tetris_Matrix::fullRow()
{
    Sint32 x,y;
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
		{
		    if(get(x,y) == NULL)
		        break;
		}
		if(x == width)
			return y;
	}
	return -1;
}



void Tetris_Matrix::drawMatrixInScene(String matName)
{
    for(Sint32 y = 0; y < height; y++)
    {
        for(Sint32 x = 0; x < width; x++)
        {
            if(get(x,y) != NULL)
                get(x,y)->drawBlocInScene(matName, Vec2f((float)(x), (float)(y)));
        }
    }
    return;
}



// debug purpose
void Tetris_Matrix::display()
{
    for(Sint32 y = height-1; y >= 0; y--)
    {
        COUT << y << (y<10?"  ":" ");
        for(Sint32 x = 0; x < width; x++)
        {
            if(get(x,y) == NULL) COUT << "[0]";
            else COUT << "[1]";
        }
        COUT << ENDL;
    }
    COUT << "    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23" << ENDL;
}

