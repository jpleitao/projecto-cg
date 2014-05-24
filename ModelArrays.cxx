#include "ModelArrays.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

ModelArrays::ModelArrays(){
    //DUMMY CONSTRUCTOR -- IN THE FUTURE DELETE THIS
    this->objectVertex = NULL;
    this->objectTexture = NULL;
    this->objectNormals = NULL;

    this->vertexIndex = NULL;
    this->normalIndex = NULL;
    this->textureIndex = NULL;

}

ModelArrays::ModelArrays(glm::vec3 *vertex, glm::vec2 *texture, glm::vec3 *normals, int* vertexInd, int* normalInd, int* textureInd, int nVertexes, int nTexels, int nNormals)
    :objectVertex(vertex), objectTexture(texture), objectNormals(normals), nVertexes(nVertexes), nTexels(nTexels), nNormals(nNormals), vertexIndex(vertexInd), normalIndex(normalInd), textureIndex(textureInd) {
        createHandles();
    }


ModelArrays::~ModelArrays() {
	if(this->objectVertex != NULL) {
        delete[] this->objectVertex;
	} 
	if(this->objectTexture != NULL) {
        delete[] this->objectTexture;
	} 
    if(this->objectNormals != NULL) {
        delete[] this->objectNormals;
    }
    if(this->vertexIndex != NULL) {
        delete[] this->vertexIndex;
    }
    if(this->normalIndex != NULL) {
        delete[] this->normalIndex;
    }
    if(this->textureIndex != NULL) {
        delete[] this->textureIndex;
    }
}

void ModelArrays::createHandles() {
    glGenBuffers(1, &this->vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->nVertexes * sizeof(glm::vec3), &objectVertex[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &this->texelsBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->texelsBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->nTexels * sizeof(glm::vec2), &objectTexture[0], GL_STATIC_DRAW);
}
