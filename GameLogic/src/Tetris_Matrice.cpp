#include "Tetris_Matrice.h"


Tetris_Matrice::Tetris_Matrice(){

  *_mat = new Tetris_Bloc[_nl*_nc];
  
  for(int i=0;i<_nl*_nc;i++){
	  _mat[i] = new Tetris_Bloc(); 
  }
}

Tetris_Bloc* Tetris_Matrice::operator[](int ligne){
  return (_mat[ligne*_nc]);
}


int Tetris_Matrice::rowFull(){
	
	bool full = true;
	int rowNum;
	
	for(int i=0;i<_nl;i++){
		for(int j=0;j<_nc;j++){	
			if(_mat[_nl][_nc].isEmpty()){
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

