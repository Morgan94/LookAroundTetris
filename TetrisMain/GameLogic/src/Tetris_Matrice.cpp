#include "Tetris_Matrice.h"


Tetris_Matrice::Tetris_Matrice(int nl,int nc){

	_nl = nl;
	_nc = nc;
	_mat = new Tetris_Bloc*[_nl*_nc];
  
	for(int i=0;i<_nl*_nc;i++){
		_mat[i] = new Tetris_Bloc(); 
	}
}

Tetris_Bloc** Tetris_Matrice::operator[](int ligne){
  return &(_mat[ligne*_nc]);
}


int Tetris_Matrice::rowFull(){
	
	bool full = true;
	int rowNum;
	
	for(int i=0;i<_nl;i++){
		full = true;
		for(int j=0;j<_nc;j++){	
			if((*this)[i][j]->isEmpty()){
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

void Tetris_Matrice::deleteRow(int num){

	for(int i=num;i>=0;i-=1){
		for(int j=0;j<_nc;j++){	
			if(i==0){
				(*this)[i][j]->setCheck(false);	
			}
			else if (i<=num){
				(*this)[i][j]->setCheck(!((*this)[i-1][j]->isEmpty()));
			}
			else{}
		}
	}
}


void Tetris_Matrice::display(){

	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){	
			if((*this)[i][j]->isEmpty()){
				std::cout<<"[0]";
			}
			else{
				std::cout<<"[1]";
			}
		}
		std::cout<<std::endl;
	}
}

