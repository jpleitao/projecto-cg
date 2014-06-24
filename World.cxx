#include "World.h"
#include "Light.h" //MAXI

World::World(ModelManager* modelManager, ObjectManager* objectManager, const char* filename)
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

    this->objectManager = objectManager;

    int c = 0;
    if(ifs) {
        if(ifs.good()) {
            while(ifs.getline(buffer, 125)) {
                c++;
                sscanf(buffer, "%s %f %f %f %f %f %f %f", modelPath, &position[0], &position[1], &position[2], &rotation[0], &rotation[1], &rotation[2], &angle);
                printf("[World Object Info] %s %f %f %f %f %f %f %f\n", modelPath, position[0], position[1], position[2], rotation[0], rotation[1], rotation[2], angle);
                tempObj = modelManager->getObject(modelPath);
                std::cout << "[Object Loaded]\n";
                tempObj->translate(position);
                tempObj->rotate(angle ,rotation);

                //FIXME: HACKED IN FOR MAXI'S TESTING
                /*if ( c == 1) {
                    Light* l = new Light(vec3(0,2,-19.19), vec3(1,0,0));
                    tempObj->setLaserLight(l);
                }*/
                worldObjects.push_back(tempObj);
                objectManager->addObject(tempObj);
            }
        }
    }
    std::cout << "[Rendering]\n";
}
