#ifndef WORLD_H

#include "Renderer.h"
#include "ModelManager.h"
#include <stdio.h>
#include <iostream>

#define WORLD_H


class World
{
    std::vector<Object*> worldObjects;
    Renderer* renderer;

public:
    World(ModelManager* modelManager, Renderer* renderer, const char* filename);
    void render();
};

#endif
