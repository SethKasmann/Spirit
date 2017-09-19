CXX 		= g++
CXXFLAGS 	= -std=c++11
SRC 		= main.cpp spirit/gfx/*.cpp spirit/geometry/*.cpp
INC			= -Ispirit/gfx -Ispirit/geometry
LFLAGS		= -lSDL2 -lGL -lGLEW

exe: main.cpp
	$(CXX) $(SRC) $(INC) $(LFLAGS) $(CXXFLAGS)

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out