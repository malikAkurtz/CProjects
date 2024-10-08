CXX = g++

CXXFLAGS = -Wall -std=c++2b -I/usr/local/SFML/include

LDFLAGS = -L/usr/local/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system

all: game

game: game.o
	${CXX} game.o -o game_out ${LDFLAGS}

# Ensure the object file is explicitly written to the output
game.o: tetris.cpp
	${CXX} ${CXXFLAGS} -c tetris.cpp -o game.o

clean:
	rm -f *.o game_out
