#include "ModelArrays.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

ModelArrays::ModelArrays(glm::vec3 *vertex, glm::vec2 *texture, glm::vec3 *normals, int* vertexInd, int* normalInd, int* textureInd)
    :objectVertex(vertex), objectTexture(texture), objectNormals(normals), vertexIndex(vertexInd), normalIndex(normalInd), textureIndex(textureInd) {}

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
