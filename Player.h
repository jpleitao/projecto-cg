#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "Renderer.h"

class Player
{
    Renderer* renderer;
    vec3 position;
    float horizAngle;
    float vertAngle;
    float fov;

    // FIXME: Maybe only temporarily constant
    const float speed;
    const float mouseSpeed;

    private:
        void updateViewMatrix(double xoff=0, double yoff=0);
        void updateProjectionMatrix(void);
    public:

        Player(Renderer* renderer, vec3 position = vec3(-9,3.6,0), float horizAngle = 7.806590, float vertAngle = -0.298797, float fov = 45.0f, float speed = 3.0f, float mouseSpeed = 0.0015f);
        void updateAngles(float screendx, float screendy);
        void updatePosition(double xoff, double yoff);

        vec3 getPosition(){return this->position;}
        void setPosition(vec3 pos){ this->position = pos;}
};

#endif // PLAYER_H
