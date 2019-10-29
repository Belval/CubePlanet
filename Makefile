CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++14 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = cube_planet

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
