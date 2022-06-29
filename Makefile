
   
#OBJS specifies which files to compile as part of the project
OBJS = main.cpp game.cpp game.hpp spriteObject.cpp spriteObject.hpp entityManager.hpp entityManager.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = output

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -Isrc\include -Lsrc\lib -lSDL2main -lSDL2 -o $(OBJ_NAME)
	$ exec ./output
