#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "common.h"
#include "Object.h"
#include <vector>

class ObjectManager {
private:
    std::vector<Object*> opaqueObjects;
    std::vector<Object*> transparentObjects;
    std::vector<Object*> allObjects;
    Renderer* renderer;

public:
    ObjectManager(Renderer* renderer);

    void setRenderer(Renderer* renderer) { this->renderer = renderer; }
    void addObject(Object* object);
    void removeObject(Object* object);

    void renderObjects();
    void collideAndFall();
    void checkLimits();
    void moveObjects();
};
#endif
