#include "ModelManager.h"

ModelManager::ModelManager(){
    this->modelArrays.clear();
    this->models.clear();
    this->textures.clear();
}

Model* ModelManager::getModel(const char* filename){
    std::string path = filename;
    path += ".model";//FIXME: The extension of the file with the model -- CHANGE THIS!

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

    Texture* texture;
    ModelArrays* objectInfo;

    //Check if texture is already loaded
    if (this->textures.find(path) != this->textures.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        texture = this->textures[path]; //FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        texture = new Texture();
        this->textures[path] = texture; //FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    //Check if modelArrays is already loaded
    if (this->modelArrays.find(path) != this->modelArrays.end()){//FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
        objectInfo = this->modelArrays[path]; //FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }
    else{
        objectInfo = new ModelArrays();
        this->modelArrays[path] = objectInfo; //FIXME: CHANGE THE KEY TO THE ONE IN THE MODEL FILE
    }

    return new Model(objectInfo, texture);
}
