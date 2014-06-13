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
    /*if(this->objectVertex != NULL) {
        glDeleteBuffers(1, &this->vertexBufferHandle);
        delete[] this->objectVertex;
	} 
	if(this->objectTexture != NULL) {
        glDeleteBuffers(1, &this->texelsBufferHandle);
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
    }  */
}

void ModelArrays::createHandles() {
    glGenBuffers(1, &this->vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->objectVertex.size() * sizeof(glm::vec3), &objectVertex[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &this->texelsBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, this->texelsBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, this->objectTexture.size() * sizeof(glm::vec2), &objectTexture[0], GL_STATIC_DRAW);
}
