#ifndef MODELARRAYS_H
#define MODELARRAYS_H

#include <string>
#include <iostream>
#include <fstream>

#include "common.h"

class ModelArrays {

    glm::vec3 *objectVertex;
    glm::vec2 *objectTexture;
    glm::vec3 *objectNormals;

    // Number of elements of each of the above arrays
    int nVertexes, nTexels, nNormals;

    int *vertexIndex;
    int *normalIndex;
    int *textureIndex;

    // Handles to the vertex buffer and UV/texture buffer we create
    GLuint vertexBufferHandle;
    GLuint texelsBufferHandle;
    //FIXME: Samething for normals, probably later on

	public:
        ModelArrays();
        ModelArrays(glm::vec3 *vertex, glm::vec2 *texture, glm::vec3 *normals, int* vertexInd, int* normalInd, int* textureInd, int nVertexes, int nTexels, int nNormals);
		~ModelArrays();

        GLuint getVertexBufferHandle() { return this->vertexBufferHandle; }
        GLuint       getTexelsHandle() { return this->texelsBufferHandle; }
        int          getNumVertexes()  { return nVertexes; }
        int          getNumTexels()    { return nTexels; }
        int          getNumNormals()   { return nNormals; }

	private:
		ModelArrays(const ModelArrays& other);
		ModelArrays& operator=(ModelArrays other);

        void createHandles();
};

#endif
