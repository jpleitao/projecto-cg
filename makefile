##
# This is practically a stub makefile which always cleans everything and rebuilds from scratch
# On mac, it assumes glfw3.h and its friends are at /usr/local/include/GLFW and that you have
# all libs symlinked at /usr/local/include. It chooses clang to compile everything
# On Linux, it assumes GLFW is at /usr/local/include/GLFW
##
UNAME_S := $(shell uname -s)


ifeq ($(UNAME_S),Linux)
    INCLUDES = -I/usr/local/include/GLFW/
    LIBS = -L/usr/local/lib/ -lglfw3 -lGL -lGLU -lX11 -lXxf86vm -lpthread -lXi -lXrandr -lGLEW
    CPP=g++
endif
ifeq ($(UNAME_S),Darwin)
    INCLUDES = -I/usr/local/include -I/usr/local/include/GLFW
    LIBS = -lglew -lglfw3 -framework opengl  
    CPP=clang++
endif

PROGRAM=projecto

SOURCES_CPP=*.cpp shaders/shader.cpp
SOURCES_CXX=*.cxx

all: clean $(PROGRAM)

clean:
	rm -rf *.o $(PROGRAM) 2>&1 > /dev/null

$(PROGRAM):
	$(CPP) $(INCLUDES) $(LIBS) $(SOURCES_CXX) $(SOURCES_CPP) -o $(PROGRAM)
