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

    int TextureID = renderer->getTextureSamplerHandle();
    ModelArrays* modelArrays = model->getObjectInfo();

    renderer->setCurrentModelMatrix(this->modelMatrix);    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);


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

    // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(renderer->getVertexUVHandle());
        glBindBuffer(GL_ARRAY_BUFFER, modelArrays->getTexelsHandle());
        glVertexAttribPointer(
            renderer->getVertexUVHandle(),                   // The attribute we want to configure
            2,                            // size : U+V => 2
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );

    glDrawArrays(GL_TRIANGLES, 0, (modelArrays->objectVertex).size());

    glDisableVertexAttribArray(renderer->getVertexUVHandle());
    glDisableVertexAttribArray(renderer->getModelVertexHandle());

}
