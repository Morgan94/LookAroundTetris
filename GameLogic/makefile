CC=g++
CFLAG=-W -fno-elide-constructors -Wall -pedantic --std=c++11
INC= -Iinclude

all: main

main: obj/main.o obj/Tetris_Matrice.o obj/Tetris_Bloc.o
	$(CC) $(CFLAG) $^ -o $@

obj/main.o: src/main_test.cpp include/Tetris_Matrice.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

obj/Tetris_Matrice.o: src/Tetris_Matrice.cpp include/Tetris_Matrice.h include/Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@

obj/Tetris_Bloc.o: src/Tetris_Bloc.cpp include/Tetris_Bloc.h
	$(CC) $(CFLAG) $(INC) -c $< -o $@
