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

/*Checks if the current object is within the limits of the cenario*/
void ObjectManager::checkLimits()
{
    for (int i=0;i<allObjects.size();i++){
        Object* current = allObjects[i];

        //Check height
        if (current->getCenterY() < MIN_Y )
            current->translate(vec3(0.0f, (MIN_Y - current->getCenterY() ), 0.0f));

        else if (current->getCenterY() > MAX_Y )
            current->translate(vec3(0.0f, (MAX_Y - current->getCenterY() ), 0.0f));

        if (!current->objectHasBoundingBox())
            continue;

        //Check X and Z positions. Get the maximum and minimum of each
        GLfloat max_x, min_x, max_z, min_z, current_x, current_z;

        max_x = current->getVertexAt(0)[0]; min_x = max_x; max_z = current->getVertexAt(0)[2]; min_z = max_z;

        for (int j=1;j<current->getVertexesSize();j++){

            current_x = current->getVertexAt(j)[0];
            current_z = current->getVertexAt(j)[2];

            if (current_x < min_x)
                min_x = current_x;

            else if (current_x > max_x)
                max_x = current_x;

            if (current_z < min_z)
                min_z = current_z;

            else if (current_z > max_z)
                max_z = current_z;
        }

        /*Compare the maximum and minimum values for the X and Z positions with the maximum and minimum allowed and perform
         *the required translactions*/
        if (min_x < MIN_X)
            current->translate(vec3((MIN_X - min_x),0.0f, 0.0f));

        if (max_x > MAX_X)
            current->translate(vec3((MAX_X - max_x),0.0f, 0.0f));

        if (min_z < MIN_Z)
            current->translate(vec3(0.0f,0.0f, (MIN_Z - min_z)));

        if (max_z > MAX_Z)
            current->translate(vec3(0.0f,0.0f, (MAX_Z - max_z)));
    }
}

void ObjectManager::moveObjects()
{
    for (int i=0;i<allObjects.size();i++){
        Object* current = allObjects[i];

        current->translate(vec3(current->getVelocityX(), 0.0f, current->getVelocityZ()));
    }
}
