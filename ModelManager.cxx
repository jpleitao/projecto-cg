#include "ModelManager.h"

ModelManager::ModelManager(){
    this->modelArrays.clear();
    this->models.clear();
    this->textures.clear();
}

Model* ModelManager::getModel(char* filename){
    char extension[] = ".model"; //FIXME: The extension of the file with the model -- CHANGE THIS!

    //Insert the code to create the model, texture and modelArrays from the file HERE

    //Change the next lines of code to go to the file and create the needed objects of Model, ModelArrays and Texture. From this
    //point on we assume that this objects are already created

    Model* model = new Model();//Create dummy Model class
    Texture* texture = new Texture();//Create dummy Texture class
    ModelArrays* modelArrays = new ModelArrays();//Create dummy ModelArrays class

    //Store the objects in the correspondent maps -- Check if the model, texture and modelArrays are already stored in the maps.
    //If the objects are not in the map, store them

    if (this->models.find(filename) == this->models.end()){//FIXME: IS THIS THE KEY???
        //Element not in map, so let's add it
        this->models[filename] = model;
    }

    if (this->textures.find(filename) == this->textures.end()){//FIXME: IS THIS THE KEY???
        //Element not in map, so let's add it
        this->textures[filename] = texture;
    }

    if (this->modelArrays.find(filename) == this->modelArrays.end()){//FIXME: IS THIS THE KEY???
        //Element not in map, so let's add it
        this->modelArrays[filename] = modelArrays;
    }

    return model;
}
