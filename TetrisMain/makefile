CC=g++
CFLAG=-Wall -pedantic --std=c++11
INC= -Iinclude

all: main

main: GameLogic/obj/main.o GameLogic/obj/Tetris_Matrice.o GameLogic/obj/Tetris_Bloc.o
	$(CC) $(CFLAG) $^ -o $@

obj/main.o: main_test.cpp GameLogic/include/Tetris_Matrice.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

obj/Tetris_Matrice.o: GameLogic/src/Tetris_Matrice.cpp GameLogic/include/Tetris_Matrice.h GameLogic/include/Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

obj/Tetris_Bloc.o: GameLogic/src/Tetris_Bloc.cpp GameLogic/include/Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@
