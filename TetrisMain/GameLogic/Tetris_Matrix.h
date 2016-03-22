#ifndef __TETRIS__TETRIS_MATRIX__
#define __TETRIS__TETRIS_MATRIX__

#include "lib/all.h"
#include "Tetris_Bloc.h"

#define MAT_WIDTH       24
#define MAT_HEIGHT      20


class Tetris_Matrix
{
    private:

        Tetris_Bloc* *mat;
        Uint8 rows;
        Uint8 cols;

    public:

        Tetris_Matrix(Uint8 _rows, Uint8 _cols);
        Tetris_Bloc** operator[](Uint8 row);
        Uint8 fullRow();
};

#endif
