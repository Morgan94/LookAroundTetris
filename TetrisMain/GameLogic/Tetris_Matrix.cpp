#include "Tetris_Matrix.h"


Tetris_Matrix::Tetris_Matrix(Uint8 _rows, Uint8 _cols)
{
    rows = _rows;
    cols = _cols;
    mat = new Tetris_Bloc*[rows * cols];

    for(Uint8 i = 0; i < rows * cols ; i++)
        mat[i] = NULL;
}

Tetris_Bloc** Tetris_Matrix::operator[](Uint8 row)
{
    return &mat[row * cols];
}


Uint8 Tetris_Matrix::fullRow()
{
	bool full = true;
	int rowNum;

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if((*this)[cols][rows]->isEmpty()){
				full = false;
			}
		}
		if(full == true){
			rowNum = i;
			return rowNum;
		}
	}
	return -1;
}

