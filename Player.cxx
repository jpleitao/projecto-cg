#include "Player.h"
#include "common.h"

Player::Player(Renderer* renderer, vec3 position, float horizAngle, float vertAngle, float fov, float speed, float mouseSpeed) :
    renderer(renderer), position(position), horizAngle(horizAngle), vertAngle(vertAngle), fov(fov), speed(speed), mouseSpeed(mouseSpeed) {

}

void Player::updateAngles(float screendx, float screendy) {
    horizAngle      += mouseSpeed * screendx;
    vertAngle       += mouseSpeed * screendy;

    updateViewMatrix();
}

void Player::updateViewMatrix(double xoff, double yoff) {
    vec3 direction = vec3( cos(vertAngle) * sin(horizAngle),  sin(vertAngle), cos(vertAngle) * cos(horizAngle) );        
    vec3 right     = vec3( sin(horizAngle - M_PI/2.0f),  0, cos(horizAngle - M_PI/2.0f) );    
    vec3 up        = glm::cross( right, direction );

    position += direction * (float)yoff;
    position += right * (float)xoff;

    renderer->setView(glm::lookAt(  position,            // He's here
                                    position+direction, // and looks here : at the same position, plus "direction"
                                    up                  // Head is up (set to 0,-1,0 to look upside-down)
                           ));
}
void Player::updatePosition(double xoff, double yoff) {
    return updateViewMatrix(speed*xoff, speed*yoff);

}
