#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>

#include "ModelArrays.h"


class ObjLoader {

    FILE* file;

	public:
		ObjLoader(const char* name);
		~ObjLoader();
		ModelArrays load();
};

#endif
