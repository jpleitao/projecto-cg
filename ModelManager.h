#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "Model.h"
#include "Object.h"
#include "ObjLoader.h"
#include "Texture.h"
#include "ModelArrays.h"
#include <map>
#include <string>
#include <fstream>
#include <iostream>


class ModelManager
{
    private:
        std::map<std::string,ModelArrays*> modelArrays;
        std::map<std::string,Model*> models;
        std::map<std::string,Texture*> textures;

    public:
        ModelManager();
        Model* getModel(const char* filename);
        Object* getObject(const char* filename);
};

#endif // MODELMANAGER_H
