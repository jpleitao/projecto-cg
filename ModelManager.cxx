#include "ModelManager.h"

ModelManager::ModelManager(){
    this->modelArrays.clear();
    this->models.clear();
    this->textures.clear();
}

Model* ModelManager::getModel(const char* filename){

    Texture* texture;
    Model* model;
    ModelArrays* model_arrays;
    ObjLoader* loader;

    std::string path = filename;
    path += ".model";

    std::cout << "[Model.getObject]Reading File: " + path << std::endl;

    //Read the .model file and extract the name of the .obj and .bmp files
    std::ifstream ifs (path.c_str(), std::ifstream::in);
    std::string texture_path, model_path;

    if (ifs){
        //Read first line, which contains the name of the .obj file

        /*I'm just assuming that the first 2 lines of the .model file are the name of the .obj file and the name of the .bmp file.
         *The next lines have the length, width and height, one per line in this order.
         */

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
    }
    else{
        std::cout<< "Unable to open file" << std::endl;
    }

    ifs.close();

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

    return model;
}

//Method that, based on a name of a model, returns an object, containing the given model and the texture attached to it
Object* ModelManager::getObject(const char* filename)
{
    Model* model;

    model = this->getModel(filename);

    //Read the .model file to get the dimentions of the object
    std::ifstream ifs (path.c_str(), std::ifstream::in);
    std::string texture_pa;

    //Create the object class and then return it
    object = new Object(model,model->getTexture());

    return object;
}
