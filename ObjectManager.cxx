#include "ObjectManager.h"
#include "Renderer.h"
#include <algorithm>

ObjectManager::ObjectManager(Renderer* renderer) : renderer(renderer)
{}

void ObjectManager::addObject(Object* object) {
    if (object->isTransparent())
        transparentObjects.push_back(object);
    else
        opaqueObjects.push_back(object);

    allObjects.push_back(object);
}
void ObjectManager::removeObject(Object* object) {
    std::vector<Object*>* vec = &opaqueObjects;
    if ( object->isTransparent() )
        vec = &transparentObjects;

    std::vector<Object*>::iterator position = std::find(vec->begin(), vec->end(), object);
    if (position != vec->end())
        vec->erase(position);

    position = std::find(allObjects.begin(), allObjects.end(), object);
    if (position != allObjects.end())
        allObjects.erase(position);
}

void ObjectManager::renderObjects() {
    glEnable(GL_CULL_FACE);
    renderer->render(opaqueObjects);
    glDisable(GL_CULL_FACE);
    renderer->render(transparentObjects);
    glEnable(GL_CULL_FACE);
}

void ObjectManager::collideAndFall() {
//Check for collisions! -- For each object test it with the ones after him
    for (int i=0;i<allObjects.size();i++){
        Object* current = allObjects[i];
        bool colide = false;

        for (int j=i+1;j<allObjects.size();j++){
            if (current->collision(allObjects[j])){
                std::cout << "COLLISION!\n";
                colide = true;
                //assert(0);
            }
        }

        if (!colide){
            //Object is not coliding with anything, so we can make it go down
            current->fall();
            for (int j=i+1;j<allObjects.size();j++){
                if (current->collision(allObjects[j])){
                    //Move the object in the opposite direction
                    current->undoFall();

                    //Stop the falling of the object
                    current->setVelocity_y(0);
                    break;
                }
            }
        }
    }
}
