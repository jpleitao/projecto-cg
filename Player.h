#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object
{

    public:
        Player();
                
        virtual void render(Renderer* renderer);
};

#endif // PLAYER_H
