#include "Model.h"

Model::Model()
{
    this->objectInfo = NULL;
    this->texture = NULL;
}

Model::Model(ModelArrays* info, Texture* text)
{
    this->objectInfo = info;
    this->texture = text;
}

Model::~Model()
{
    free(this->objectInfo);
    free(this->texture);
}
