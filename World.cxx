#include "World.h"

World::World(ModelManager* modelManager, Renderer* renderer, const char* filename)
{
    glm::vec3 position;
    glm::vec3 rotation;
    Object* tempObj;
    char buffer[125];
    GLfloat angle;

    std::string path = filename;
    path += ".world";

    std::cout << "[Creating World]Reading file: " + path << std::endl;

    std::ifstream ifs (path.c_str(), std::ifstream::in);
    char modelPath[25];

    this->renderer = renderer;

    if(ifs) {
        if(ifs.good()) {
            while(ifs.getline(buffer, 125)) {
                sscanf(buffer, "%s %f %f %f %f %f %f %f", modelPath, &position[0], &position[1], &position[2], &rotation[0], &rotation[1], &rotation[2], &angle);
                tempObj = modelManager->getObject(modelPath);
                tempObj->translate(position);
                tempObj->rotate(angle ,rotation);
                worldObjects.push_back(tempObj);
            }
        }
    }

    (this->renderer)->render(worldObjects);
}
