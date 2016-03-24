CC=g++
CFLAG=-Wall -pedantic --std=c++11
INC= -Iinclude

all: main

main: GameLogic/obj/main.o GameLogic/obj/Tetris_Matrice.o GameLogic/obj/Tetris_Bloc.o
	$(CC) $(CFLAG) $^ -o $@

GameLogic/obj/main.o: main_test.cpp Tetris_Matrice.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

GameLogic/obj/Tetris_Matrice.o: GameLogic/src/Tetris_Matrice.cpp Tetris_Matrice.h Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

GameLogic/obj/Tetris_Bloc.o: GameLogic/src/Tetris_Bloc.cpp Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@
