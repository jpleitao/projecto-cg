#include "Object.h"
#include "Renderer.h"

Object::Object(Model* model, Texture* texture) : model(model), texture(texture), modelMatrix(mat4(1.0f))
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

void Object::render(Renderer* renderer) {

    //Update MVP
    renderer->setCurrentModelMatrix(modelMatrix);    

    //Draw the model with the texture mapped
    texture->beginRender(renderer, model);
    model->beginRender(renderer);

    model->draw(renderer);
    
    model->finishRender(renderer);
    texture->finishRender(renderer, model);
}
