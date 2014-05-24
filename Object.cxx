#include "Object.h"

Object::Object(Model* model) : model(model), modelMatrix(mat4(1.0f))
{
}

void Object::rotate(GLfloat angle, vec3 axis) {
    this->modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

void Object::scale(vec3 scaleVec) {
    this->modelMatrix = glm::scale(modelMatrix, scaleVec);
}
void Object::translate(vec3 vec) {
    this->modelMatrix = glm::translate(modelMatrix, vec);
}
void Object::resetTransforms() {   
    //Turn modelMatrix into the identity matrix 
    this->modelMatrix = mat4(1.0f); 
}

void Object::render() {

}
