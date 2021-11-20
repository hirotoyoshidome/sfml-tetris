CC = gcc
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(patsubst %/,%,$(dir $(mkfile_path)))

# LD_LIBRARY_PATH := $(current_dir)/libs/SFML-2.5.1/lib/
# LD_LIBRARY_PATH := $(current_dir)/libs/SFML-2.5.1-macos-clang/lib

.PHONY:	help	compile	link	all	compile-mac	link-mac	all-mac	ldd-mac	clean	setup	docker-run	docker-exec	docker-stop
.SILENT:

help:
	@echo 1. compile
	@echo 2. link
	@echo 3. exec at your command line.
compile:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1/include

link:
	g++ main.o -o MAIN -L ./libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

all:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1/include \
	&& g++ main.o -o MAIN -L ./libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	export LD_LIBRARY_PATH=./libs/SFML-2.5.1/lib && ./MAIN

compile-mac:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1-macos-clang/include

link-mac:
	g++ main.o -o MAIN_MAC -L ./libs/SFML-2.5.1-macos-clang/lib -lsfml-graphics -lsfml-window -lsfml-system

all-mac:
	g++ -o main.o -c main.cpp -I ./libs/SFML-2.5.1-macos-clang/include \
	&& g++ main.o -o MAIN_MAC -L ./libs/SFML-2.5.1-macos-clang/lib -lsfml-graphics -lsfml-window -lsfml-system

ldd-mac:
	otool -L ./MAIN_MAC

clean:
	rm -f *.o

setup:
	docker build -t ubuntu-tetris:latest .

docker-run:
	docker run --rm -d -it --name tetris -v $(current_dir):/var/dev ubuntu-tetris:latest

docker-exec:
	docker exec -it tetris bash

docker-stop:
	docker stop tetris
