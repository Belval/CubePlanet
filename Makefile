CXX = g++
CXXFLAGS = -Wall -std=c++14
LDFLAGS =  -lGL -lglut -lGLU -lGLEW -lIL -lILU -lILUT -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = cube_planet

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
