#ifndef WORLD_H

#include "ObjectManager.h"
#include "ModelManager.h"
#include <stdio.h>
#include <iostream>

#define WORLD_H


class World
{
    std::vector<Object*> worldObjects;
    ObjectManager* objectManager;

public:
    World(ModelManager* modelManager, ObjectManager* renderer, const char* filename);
};

#endif
