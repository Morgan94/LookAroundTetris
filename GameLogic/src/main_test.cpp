#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Tetris_Matrice.h"

int main(){
	
	Tetris_Matrice *tm = new Tetris_Matrice(width, height);

	bool defeat = false;
	while(defeat == false){

		for(int j=0;j<width;j++){	
			(*tm)[23][j]->setCheck(true);
			(*tm)[22][j]->setCheck(true);
			(*tm)[21][j]->setCheck(true);
			(*tm)[20][j]->setCheck(true);
		}
		for(int i=4;i<height;i++){	
			(*tm)[i][5]->setCheck(true);
			(*tm)[i][6]->setCheck(true);
			(*tm)[i][7]->setCheck(true);
			(*tm)[i][8]->setCheck(true);
			(*tm)[i][9]->setCheck(true);
			(*tm)[i][10]->setCheck(true);

		}	
		tm->display();
		std::cout<<std::endl;
		int num = 0;
		while(num != -1){
			//std::cout<<"sloubi2"<<std::endl;
			num = tm->rowFull();
			tm->deleteRow(num);
		}
		tm->display();
		std::cout<<std::endl;
		
		(*tm)[2][5]->setCheck(true);
		(*tm)[3][5]->setCheck(true);
		(*tm)[4][5]->setCheck(true);
		(*tm)[5][5]->setCheck(true);
		(*tm)[6][5]->setCheck(true);
		(*tm)[7][5]->setCheck(true);
		
		tm->display();
		
		std::cout<<"defeat?"<<std::endl;
		defeat = tm->defeat();
		std::cout<<defeat<<std::endl;
		
		
	}

    delete tm;	
}
