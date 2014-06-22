#include "Light.h"


Light::Light(vec3 pos, vec3 intensities, vec3 specular, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
: position(pos), intensities(intensities), specular(specular), renderer(NULL), constantAttenuation(constantAttenuation), linearAttenuation(linearAttenuation),
quadraticAttenuation(quadraticAttenuation)
{}

Light::~Light() {
    if ( renderer ) renderer->removeLight(this);
}
