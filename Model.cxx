#include "Model.h"

Model::Model(ModelArrays* info, Texture* text)
{
    this->objectInfo = info;
    this->texture = text;
}

Model::~Model()
{
    if ( this->objectInfo ) delete this->objectInfo;

    if ( this->texture) delete this->texture;
}
