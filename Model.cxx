#include "Model.h"
#include "ObjLoader.h"

Model::Model(ModelArrays* info, Texture* text)
{
    if ( info == NULL && text == NULL ) {
        this->objectInfo = ObjLoader("data/models/dummy.obj").load();
        printf("New MODEL: %p\n", this->objectInfo);
    }  else {
        this->objectInfo = info;
        this->texture = text;
    }
}

Model::~Model()
{
    if ( this->objectInfo ) delete this->objectInfo;

    if ( this->texture) delete this->texture;
}
