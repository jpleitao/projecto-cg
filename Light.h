#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"
#include "Renderer.h"

class Light {
private:
    vec3 position;
    vec3 intensities;
    Renderer* renderer;
    float constantAttenuation, linearAttenuation, quadraticAttenuation;
public:
    Light(vec3 pos=vec3(0,0,0), vec3 intensities=vec3(0,0,0), float constantAttenuation=1, float linearAttenuation=0, float quadraticAttenuation=0.2);
    ~Light();

    void setPosition(vec3 pos)    { this->position = pos; }
    void setIntensities(vec3 intensities) { this->intensities = intensities; }

    vec3 getPosition() { return this->position; }
    vec3 getIntensities() { return this->intensities; }
    float getConstantAttenuation() { return this->constantAttenuation; }
    float getLinearAttenuation() { return this->linearAttenuation; }
    float getQuadraticAttenuation() { return this->quadraticAttenuation; }

    void setRenderer(Renderer* r) { this->renderer = r; }
};

#endif
