#ifndef COMMON_H
#define COMMON_H

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <math.h>

//Just for testing...
#include <assert.h>

#ifndef M_PI
 #define M_PI 3.1415926535897932384626433832795
#endif

#ifndef OBS_H
 #define OBSERVER_HEIGHT 3.6
 #define MAX_X 17
 #define MIN_X -17
 #define MIN_Y 0
 #define MAX_Y 5
 #define MAX_Z 17
 #define MIN_Z -17
#endif

#endif
