#include "Object.h"
#include "Renderer.h"

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


void Object::render(Renderer* renderer) {

    ModelArrays* modelArrays = model->getObjectInfo();

    renderer->setCurrentModelMatrix(this->modelMatrix);    

    // TODO: Handle textures!!!!! See tutorial 7

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(renderer->getModelVertexHandle());
    glBindBuffer(GL_ARRAY_BUFFER, modelArrays->getVertexBufferHandle());
    glVertexAttribPointer(
        renderer->getModelVertexHandle(),  // The attribute we want to configure
        3,    // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    // TODO: Handle textures!!!!!!! See tutorial 7
    glDrawArrays(GL_TRIANGLES, 0, modelArrays->getNumVertexes() );

}
