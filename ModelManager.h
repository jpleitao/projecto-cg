#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <map>
#include "Model.h"
#include "Texture.h"
#include "ModelArrays.h"


class ModelManager
{
    private:
        std::map<char*,ModelArrays*> modelArrays;
        std::map<char*,Model*> models;
        std::map<char*,Texture*> textures;

    public:
        ModelManager();
        Model* getModel(char* filename);
};

#endif // MODELMANAGER_H
