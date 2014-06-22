#include "Light.h"


Light::Light(vec3 pos, vec3 intensities, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
: position(pos), intensities(intensities), renderer(NULL), constantAttenuation(constantAttenuation), linearAttenuation(linearAttenuation),
quadraticAttenuation(quadraticAttenuation)
{}

Light::~Light() {
    if ( renderer ) renderer->removeLight(this);
}
