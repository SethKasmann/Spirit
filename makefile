CXX 		= g++
CXXFLAGS 	= -std=c++11
SRC 		= main.cpp spirit/gfx/*.cpp
INC			= -Ispirit/gfx -Ispirit/glm -Ispirit/glm/detail -Ispirit/glm/gtc -Ispirit/glm/gtx -Ispirit/glm/simd
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