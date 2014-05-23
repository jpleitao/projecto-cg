#include "Model.h"

Model::Model(ModelArrays* info=NULL, Texture* text=NULL)
{
    this->objectInfo = info;
    this->texture = text;
}

Model::~Model()
{
    delete this->objectInfo;
    delete this->texture;
}
