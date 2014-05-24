#include "ModelManager.h"

ModelManager::ModelManager(){
    this->modelArrays.clear();
    this->models.clear();
    this->textures.clear();
}

Model* ModelManager::getModel(char* filename){
    std::string path = filename;
    path.append(".model");//FIXME: The extension of the file with the model -- CHANGE THIS!

    std::cout << "FILE: " + path << std::endl;

    //Insert the code to create the model, texture and modelArrays from the file HERE

    if (this->models.find(path) != this->models.end())//Model exists
        return this->models[path];

    //Model does not exist

    ////
    /// Dummy code that reads the model file -- Start
    ///

    std::ifstream ifs (path.c_str(), std::ifstream::in);
    std::string line;

    if (ifs){
        while (ifs.good()){
            std::getline(ifs, line);
            std::cout << line << std::endl;
        }
    }
    else{
        std::cout<< "Unable to open file" << std::endl;
    }

    ifs.close();

    ///////
    /// Dummy code that reads the model file -- End
    ///

    Model* model = new Model();//Create dummy Model class

    //Check if texture is already loaded
    if (this->textures.find(path) != this->textures.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        model->setTexture(this->textures[path]);//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        model->setTexture(new Texture());//Create dummy Texture class
        this->textures[path] = model->getTexture();//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    //Check if modelArrays is already loaded
    if (this->modelArrays.find(path) != this->modelArrays.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        model->setObjectInfo(this->modelArrays[path]);//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        model->setObjectInfo(new ModelArrays());//Create dummy ModelArrays class
        this->modelArrays[path] = model->getObjectInfo();//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    return model;
}
