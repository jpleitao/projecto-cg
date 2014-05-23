#ifndef MODELARRAYS_H
#define MODELARRAYS_H

#include <string>
#include <iostream>
#include <fstream>

#include <GL/gl.h>

class ModelArrays {

    glm::vec3 *objectVertex;
    glm::vec2 *objectTexture;
    glm::vec3 *objectNormals;

    int *vertexIndex;
    int *normalIndex;
    int *textureIndex;

	public:
        ModelArrays::ModelArrays(glm::vec3 vertex, glm::vec3 texture, glm::vec3 normals, int* vertexInd, int* normalInd, int* textureIndex);
		~ModelArrays();

	private:
		ModelArrays(const ModelArrays& other);
		ModelArrays& operator=(ModelArrays other);
};

#endif
