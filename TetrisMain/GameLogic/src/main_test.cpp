#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tetris_Matrice.h"

int main(){
	
	Tetris_Matrice *tm = new Tetris_Matrice(width, height);

    (*tm)[0][0]->setCheck(true);
    std::cout << (*tm)[0][0]->isEmpty() << std::endl;

	for(int j=0;j<width;j++){	
		(*tm)[23][j]->setCheck(true);
		(*tm)[22][j]->setCheck(true);
		(*tm)[21][j]->setCheck(true);
		(*tm)[20][j]->setCheck(true);
		(*tm)[19][j]->setCheck(true);
		(*tm)[18][j]->setCheck(true);
	}
	for(int i=0;i<height;i++){	
		(*tm)[i][5]->setCheck(true);
		(*tm)[i][6]->setCheck(true);
		(*tm)[i][7]->setCheck(true);
		(*tm)[i][8]->setCheck(true);
		(*tm)[i][9]->setCheck(true);
		(*tm)[i][10]->setCheck(true);

	}
	
	tm->display();
	std::cout << tm->rowFull()<< std::endl;
	
	int num;
	while(num != -1){
		num = tm->rowFull();
		tm->deleteRow(num);
	}
	tm->display();

    delete tm;	
}
