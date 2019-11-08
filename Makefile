CXX = g++
CXXFLAGS = -Wall -std=c++14
LDFLAGS =  -lglut -lGLU -lGLEW -lGL -lIL -lILU -lILUT -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = cube_planet

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LBLIBS) $(LDFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC)
