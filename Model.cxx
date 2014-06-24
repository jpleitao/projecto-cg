#include "Model.h"
#include "ObjLoader.h"
#include "Renderer.h"

Model::Model(ModelArrays* info, Texture* text, int primitiveType)
{
    if ( info == NULL && text == NULL ) {
        this->objectInfo = ObjLoader("data/models/obj/dummy.obj").load();
        printf("New MODEL: %p\n", this->objectInfo);
    }  else {
        this->objectInfo = info;
        this->texture = text;
    }
    this->primitiveType = primitiveType;   
}

void Model::beginRender(Renderer* renderer) {
    glEnableVertexAttribArray(renderer->getModelVertexHandle());
    glBindBuffer(GL_ARRAY_BUFFER, objectInfo->getVertexBufferHandle());
    glVertexAttribPointer(
        renderer->getModelVertexHandle(),  // The attribute we want to configure
        3,    // size
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );

    if ( objectInfo->hasNormals() ) {
        glEnableVertexAttribArray(renderer->getNormalsHandle());
        glBindBuffer(GL_ARRAY_BUFFER, objectInfo->getNormalsHandle());
        glVertexAttribPointer(
            renderer->getNormalsHandle(),  // The attribute we want to configure
            3,    // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
        );
    }
}

void Model::finishRender(Renderer* renderer) {
    glDisableVertexAttribArray(renderer->getNormalsHandle());
    glDisableVertexAttribArray(renderer->getModelVertexHandle());
}

void Model::draw(Renderer* renderer) {
    //printf("Drawing a model!\n");
    glDrawArrays(this->primitiveType, 0, objectInfo->objectVertex.size());
}

Model::~Model()
{
    if ( this->objectInfo ) delete this->objectInfo;

    if ( this->texture) delete this->texture;
}
