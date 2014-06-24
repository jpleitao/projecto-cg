#include "ModelArrays.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

ModelArrays::ModelArrays(){
}

ModelArrays::ModelArrays(std::vector<glm::vec3> vertex, std::vector<glm::vec2> texture, std::vector<glm::vec3> normals)
    :objectVertex(vertex), objectTexture(texture), objectNormals(normals) {
        createHandles();
    }


ModelArrays::~ModelArrays() {
    if(this->objectVertex.size() > 0) {
        glDeleteBuffers(1, &this->vertexBufferHandle);
	} 
	if(this->objectTexture.size() > 0) {
        glDeleteBuffers(1, &this->texelsBufferHandle);
	} 
    if(this->objectNormals.size() > 0) {
        glDeleteBuffers(1, &this->normalsBufferHandle);
    }
}

void ModelArrays::createHandles() {
    glGenBuffers(1, &this->vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->objectVertex.size() * sizeof(glm::vec3), &objectVertex[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->texelsBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->texelsBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->objectTexture.size() * sizeof(glm::vec2), &objectTexture[0], GL_STATIC_DRAW);

    glGenBuffers(1, &this->normalsBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->objectNormals.size() * sizeof(glm::vec3), &objectNormals[0], GL_STATIC_DRAW);
}
