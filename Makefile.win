#CXX         := g++
#CXXFLAGS    := -lSDL2 -lSDL2_image 
#CXXINCLUDES := -I/usr/include/SDL2 -Iinclude/
#CXXLIBS     := -L/usr/lib

SRC     := src/
OBJ     := build/
DEP     := build/

PROGNAME:= "program.exe"
CPPS    := $(shell dir ./src/)
SOURCES := $(patsubst %.cpp, $(SRC)%.cpp, $(CPPS))
OBJECTS := $(patsubst %.cpp, $(OBJ)%.obj, $(CPPS))
DEPENDS := $(patsubst %.cpp, $(DEP)%.d  , $(CPPS))

WARNING := 
COMPILE := $(CXX) $(WARNING) $(CXXFLAGS) $(CXXLIBS) $(CXXINCLUDES)

# .PHONY means these rules get executed even if files of those names exist.
.PHONY: all clean

-include $(DEPENDS)

# Fresh installation
install: default


# Linking the executable from the object files
default: $(OBJECTS)
	link $(OBJECTS) -OUT:$(PROGNAME) -LIBPATH:C:/Framework/SDL2_ttf-2.20.1/lib/x64 -LIBPATH:C:/Framework/SDL2_image-2.6.1/lib/x64 /LIBPATH:C:/Framework/SDL2-2.0.22/lib/x64 SDL2_ttf.lib SDL2.lib SDL2main.lib user32.lib shell32.lib SDL2_image.lib -SUBSYSTEM:CONSOLE -MACHINE:X64



# Independent object compilation
$(OBJ)%.obj: $(SRC)%.cpp Makefile
	cl -Zi -EHsc -W3 -c $< -Fo"./build/" -std:c++17 -I "C:/Framework/SDL2-2.0.22/include" -I "C:/Framework/SDL2_image-2.6.1/include" -I "C:/Framework/SDL2_ttf-2.20.1/include" -I "./include"


# Wipe out old materials
clean:
	$(RM) $(OBJECTS) $(DEPENDS) default
