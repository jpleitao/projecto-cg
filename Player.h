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
    std::vector<glm::vec4> hit_box;

    // FIXME: Maybe only temporarily constant
    const float speed;
    const float mouseSpeed;

    vec2 directionProjectionXoZ;

    private:
        void updateViewMatrix(double xoff=0, double yoff=0);
        void updateProjectionMatrix(void);
    public:

        Player(Renderer* renderer, vec3 position = vec3(-9,3.6,0), float horizAngle = 7.806590, float vertAngle = -0.298797, float fov = 45.0f, float speed = 12.0f, float mouseSpeed = 0.0015f);
        void updateAngles(float screendx, float screendy);
        void updatePosition(double xoff, double yoff);
        void updatePosition(vec3 position);

        vec3 getPosition(){return this->position;}
        void setPosition(vec3 pos){ this->position = pos;}
        std::vector<glm::vec4> getHitBox(){return this->hit_box;}
        void createHitBox();

        vec2 getDirectionProjectionXoZ(){return this->directionProjectionXoZ;}

        bool colideWithObject(Object* obj);
};

#endif // PLAYER_H
