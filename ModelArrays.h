#ifndef MODELARRAYS_H
#define MODELARRAYS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "common.h"

class ModelArrays {

public:
    std::vector<glm::vec3> objectVertex;
    std::vector<glm::vec2> objectTexture;
    std::vector<glm::vec3> objectNormals;

    // Handles to the vertex buffer and UV/texture buffer we create
    GLuint vertexBufferHandle;
    GLuint texelsBufferHandle;
    GLuint normalsBufferHandle;

	public:
        ModelArrays();
        ModelArrays(std::vector<glm::vec3> vertex, std::vector<glm::vec2> texture, std::vector<glm::vec3> normals);
		~ModelArrays();

        GLuint getVertexBufferHandle() { return this->vertexBufferHandle; }
        GLuint       getTexelsHandle() { return this->texelsBufferHandle; }
        GLuint      getNormalsHandle() { return this->normalsBufferHandle; }

        bool hasNormals() { return objectNormals.size() != 0;}
        bool hasUVs()     { return objectTexture.size() != 0;}

	private:
		ModelArrays(const ModelArrays& other);
		ModelArrays& operator=(ModelArrays other);

        void createHandles();
};

#endif
