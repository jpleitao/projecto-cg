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

Texture* Model::getTexture(){
    return this->texture;
}

ModelArrays* Model::getObjectInfo(){
    return this->objectInfo;
}

void Model::setTexture(Texture* text){
    this->texture = text;
}

void Model::setObjectInfo(ModelArrays* model){
    this->objectInfo = model;
}
