
   
#OBJS specifies which files to compile as part of the project
OBJS = main.cpp game.cpp game.hpp spriteObject.cpp spriteObject.hpp entityManager.hpp entityManager.cpp backgroundManager.cpp backgroundManager.hpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = output

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -I/usr/include/SDL2 -L/usr/lib -lSDL2 -lSDL2_image -o $(OBJ_NAME)
	$ exec ./output
