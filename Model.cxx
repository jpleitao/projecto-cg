#include "Model.h"

Model::Model(ModelArrays* info, Texture* text)
{
    this->objectInfo = info;
    this->texture = text;
}

Model::~Model()
{
    delete this->objectInfo;
    delete this->texture;
}
