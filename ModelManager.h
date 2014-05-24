#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <map>
#include <string>
#include "Model.h"
#include "Texture.h"
#include "ModelArrays.h"


class ModelManager
{
    private:
        std::map<std::string,ModelArrays*> modelArrays;
        std::map<std::string,Model*> models;
        std::map<std::string,Texture*> textures;

    public:
        ModelManager();
        Model* getModel(char* filename);
};

#endif // MODELMANAGER_H
