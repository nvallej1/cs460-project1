GL_FLAGS=-lglut -lGLU -lGL
OTHER_FLAGS=-Wall -Wunused -pedantic
FLAGS=$(GL_FLAGS) $(OTHER_FLAGS)

all: proj1

proj1:
	g++ $(FLAGS) proj1.cpp -o a.out

clean:
	rm -f *.o *.out
