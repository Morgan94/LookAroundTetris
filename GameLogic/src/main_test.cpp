#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tetris_Matrice.h"

int main(){
	
	Tetris_Matrice *tm = new Tetris_Matrice(width, height);

    (*tm)[0][0]->setCheck(true);
    std::cout << tm->operator[](0)[0]->isEmpty() << std::endl;


	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){	
			(*tm)[5][j]->setCheck(true);
		}
	}
	
	tm->display();
	std::cout << tm->rowFull()<< std::endl;

    delete tm;	
}
