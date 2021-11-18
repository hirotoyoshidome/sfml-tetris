.SILENT:
compile:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1/include

link:
	g++ main.o -o MAIN -L ./libs/SFML-2.5.1/include/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	export LD_LIBRARY_PATH=./libs/SFML-2.5.1/include/lib && ./MAIN
