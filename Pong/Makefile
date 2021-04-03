#compiler
CXX = g++

#flags used by the compiler
CXXFLAGS = -Wall -Wextra -O3 -std=c++14

LIBS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

#name of the executable
EXEC = pong-game.out

#build directories
RELEASE_BUILD = out/build
OBJ_DIR = obj
SOURCEDIR = src

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)

OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
OBJECTS := $(notdir $(OBJECTS))
OBJECTS := $(addprefix $(RELEASE_BUILD)/$(OBJ_DIR)/, $(OBJECTS))

all:
	\mkdir -p $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SOURCES) 
	\mv -f *.o $(RELEASE_BUILD)/$(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	\mv -f $(EXEC) $(RELEASE_BUILD)/
	
clean:
	rm -f $(wildcard $(RELEASE_BUILD)/$(OBJ_DIR)/*.o)
	rm -f $(wildcard *.o)