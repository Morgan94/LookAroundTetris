#ifndef __TETRIS__MATRIX__
#define __TETRIS__MATRIX__

#include "lib/all.h"

#define MATRIX_WIDTH        24
#define MATRIX_HEIGHT       20

#include "GamePhysic/Tetris_3DBloc.h"
#include "GamePhysic/Tetris_Shape.h"



/* OpenGL axes VS Matrix axes

y              //  0--------> x
               //  |[][][][]...
^              //  |[][][][]...
|              //  |[][][][]...
|              //  v...
|              //
0---------> x  //  y

     Bloc(x,y) == Mat[y][x]
*/

class Tetris_Shape;
class Tetris_Matrix
{
private:

    Tetris_3DBloc** blocs;
    Sint32 width;
    Sint32 height;

public:

    Tetris_Matrix(Sint32 _width = MATRIX_WIDTH, Sint32 _height = MATRIX_HEIGHT);
    // get/set
    Tetris_3DBloc** operator[](Sint32 y);
    Tetris_3DBloc** at(Sint32 x, Sint32 y);
    Tetris_3DBloc* get(Sint32 x, Sint32 y);
    void set(Sint32 x, Sint32 y, Tetris_3DBloc* bloc);
    // logic
    void deleteRow(Sint32 row);
    Sint32 fullRow();
    // physic link
    void addShapeToMatrix(Tetris_Shape* shape);
    void removeBloc(Sint32 x, Sint32 y);
    void drawMatrixInScene(String matName);
    bool defeat();

    // debug purpose
    void display();

};


#endif
