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

    std::cout << "[Model.getModel]Reading File: " + path << std::endl;

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
            assert(0);
        }

        //Read second line, which contains the name of the texture (.bmp) file
        if (ifs.good()){
            std::getline(ifs, texture_path);
            std::cout << "Texture in file: " << texture_path << std::endl;
        }
        else{
            std::cout << "Could not read the texture file_path!" << std::endl;
            assert(0);
        }
    }
    else{
        std::cout<< "Unable to open file" << std::endl;
        assert(0);
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
    GLfloat cube_size;
    Model* model;
    Object* object;
    std::string path = filename;
    path += ".model";

    model = this->getModel(filename);

    //Read the .model file to get the side of the object
    std::ifstream ifs (path.c_str(), std::ifstream::in);
    std::string line;
    std::vector<glm::vec4> vert;
    GLfloat lenght, width, height;
    GLfloat x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    std::cout << "[Model.getObject]Reading File: " + path << std::endl;

    bool bound = false;

    if (ifs){
        //Skip first two lines
        std::getline(ifs, line);
        std::getline(ifs, line);

        //Read the object's bounding box and height
        if (ifs.good()){
            std::getline(ifs,line);
            sscanf(line.c_str(), "%f,%f,%f %f,%f,%f %f,%f,%f %f,%f,%f %f",
                                  &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &x4, &y4, &z4, &height);
            bound = true;
        }
    }
    else{
        std::cout<< "Unable to open file" << std::endl;
        assert(0);
    }

    ifs.close();

    //Create the array with the positions of the object's top face
    vert.push_back(glm::vec4(x1,y1,z1,1));
    vert.push_back(glm::vec4(x2,y2,z2,1));
    vert.push_back(glm::vec4(x3,y3,z3,1));
    vert.push_back(glm::vec4(x4,y4,z4,1));

    width = sqrt( (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) + (z1-z2) * (z1-z2) );
    lenght = width;

    //Create the object class and then return it
    object = new Object(model,model->getTexture(),bound,lenght,width,height,vert);

    return object;
}
