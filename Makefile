CC = gcc

.SILENT:
compile:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1/include

link:
	g++ main.o -o MAIN -L ./libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	export LD_LIBRARY_PATH=$(pwd)/libs/SFML-2.5.1/lib && ./MAIN

all:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1/include \
	&& g++ main.o -o MAIN -L ./libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system \
	&& export LD_LIBRARY_PATH=$(pwd)/libs/SFML-2.5.1/lib && ./MAIN
