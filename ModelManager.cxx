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

//Method that, based on a name of a model, returns an object, containing the given model and the texture attached to it
Object* ModelManager::getObject(const char* filename)
{
    Texture* texture;
    Model* model;
    ModelArrays* model_arrays;
    Object* object;
    ObjLoader* loader;

    std::string path = filename;
    path += ".model";

    std::cout << "[Model.getObject]Reading File: " + path << std::endl;

    //Read the .model file and extract the name of the .obj and .bmp files
    std::ifstream ifs (path.c_str(), std::ifstream::in);
    std::string texture_path, model_path;

    if (ifs){
        //Read first line, which contains the name of the .obj file
        if (ifs.good()){
            std::getline(ifs, model_path);
            std::cout << "Model in file: " << model_path << std::endl;
        }
        else{
            std::cout << "Could not read the model file_path!" << std::endl;
        }

        //Read second line, which contains the name of the texture (.bmp) file
        if (ifs.good()){
            std::getline(ifs, texture_path);
            std::cout << "Texture in file: " << texture_path << std::endl;
        }
        else{
            std::cout << "Could not read the texture file_path!" << std::endl;
        }

        /*I'm just assuming that we have 2 lines, one with the .obj file and another with the .bmp file, but if we have more
         *this can be adapted without that much of a problem
        */
    }
    else{
        std::cout<< "Unable to open file" << std::endl;
    }

    //Check if we have an .obj file for the given model -- FIXME FIXME FIXME FIXME
    if(model_path.empty())
        assert(0);

    //Load the .obj file, checking first if it is stored in the hashtable of objects (Model*) or not
    if (this->modelArrays.find(path) != this->modelArrays.end())
        model_arrays = this->modelArrays[model_path];

    else{
        loader = new ObjLoader(model_path.c_str());
        model_arrays = loader->load();
        this->modelArrays[model_path] = model_arrays;
    }

    //Check if we have a .bmp file for the given texture -- FIXME FIXME FIXME FIXME
    if(texture_path.empty())
        assert(0);

    //Load the texture, checking first if it is stored in the hashtable of textures or not
    if (this->textures.find(texture_path) != this->textures.end())
        texture = this->textures[texture_path];

    else{
        texture = new Texture(texture_path.c_str());
        this->textures[texture_path] = texture;
    }

    //Create the model
    model = new Model(model_arrays,texture);

    //Create the object class and then return it
    object = new Object(model,texture);

    return object;
}
