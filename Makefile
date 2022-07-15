CXX         := g++
CXXFLAGS    := -lSDL2 -lSDL2_image 
CXXINCLUDES := -I/usr/include/SDL2 -Iinclude/
CXXLIBS     := -L/usr/lib

SRC     := src/
OBJ     := build/
DEP     := build/

PROGNAME:= "program"
CPPS    := $(shell dir ./src/)
SOURCES := $(patsubst %.cpp, $(SRC)%.cpp, $(CPPS))
OBJECTS := $(patsubst %.cpp, $(OBJ)%.o  , $(CPPS))
DEPENDS := $(patsubst %.cpp, $(DEP)%.d  , $(CPPS))

WARNING := 
COMPILE := $(CXX) $(WARNING) $(CXXFLAGS) $(CXXLIBS) $(CXXINCLUDES)

# .PHONY means these rules get executed even if files of those names exist.
.PHONY: all clean

# Default make command execute
all: default

# Wipe out old materials
clean:
	$(RM) $(OBJECTS) $(DEPENDS) default

-include $(DEPENDS)
# Linking the executable from the object files
default: $(OBJECTS)
	$(COMPILE) $^ -o $(PROGNAME)

# Fresh installation
install:
	$(COMPILE) $(OBJECTS) -o $(PROGNAME)

# Independent object compilation
$(OBJ)%.o: $(SRC)%.cpp Makefile
	$(COMPILE) -MMD -MP -c $< -o $@
