#ifndef MODELARRAYS_H
#define MODELARRAYS_H

#include <string>
#include <iostream>
#include <fstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

class ModelArrays {

    glm::vec3 *objectVertex;
    glm::vec2 *objectTexture;
    glm::vec3 *objectNormals;

    int *vertexIndex;
    int *normalIndex;
    int *textureIndex;

	public:
        ModelArrays(glm::vec3 *vertex, glm::vec2 *texture, glm::vec3 *normals, int* vertexInd, int* normalInd, int* textureInd);
		~ModelArrays();

	private:
		ModelArrays(const ModelArrays& other);
		ModelArrays& operator=(ModelArrays other);
};

#endif
