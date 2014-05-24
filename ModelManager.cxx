#include "ModelManager.h"

ModelManager::ModelManager(){
    this->modelArrays.clear();
    this->models.clear();
    this->textures.clear();
}

Model* ModelManager::getModel(char* filename){
    std::string path = filename + ".model";//FIXME: The extension of the file with the model -- CHANGE THIS!

    //Insert the code to create the model, texture and modelArrays from the file HERE

    if (this->models.find(path) != this->models.end())//Model exists
        return this->models[path];

    //Model does not exist

    ////
    /// Dummy code that reads the model file -- Start
    ///


    ///////
    /// Dummy code that reads the model file -- End
    ///

    Model* model = new Model();//Create dummy Model class

    //Check if texture is already loaded
    if (this->textures.find(path) != this->textures.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        model->texture = this->textures[path];//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        model->texture = new Texture();//Create dummy Texture class
        this->textures[path] = model->texture;//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    //Check if modelArrays is already loaded
    if (this->modelArrays.find(path) != this->modelArrays.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        model->objectInfo = this->modelArrays[path];//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        model->objectInfo = new modelArrays();//Create dummy ModelArrays class
        this->modelArrays[path] = model->objectInfo;//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    return model;
}
