#include "Player.h"
#include "common.h"

Player::Player(Renderer* renderer, vec3 position, float horizAngle, float vertAngle, float fov, float speed, float mouseSpeed) :
    renderer(renderer), position(position), horizAngle(horizAngle), vertAngle(vertAngle), fov(fov), speed(speed), mouseSpeed(mouseSpeed) {
        updateViewMatrix();

        //Initialize hit box based on current player's positions
}

void Player::updateAngles(float screendx, float screendy) {
    horizAngle      += mouseSpeed * screendx;
    vertAngle       += mouseSpeed * screendy;

    if ( vertAngle < -M_PI/2 ) vertAngle = -M_PI/2;
    else if ( vertAngle > M_PI/2 ) vertAngle = M_PI/2;

    if ( horizAngle > 2*M_PI ) horizAngle -= 2*M_PI;
    else if ( horizAngle < -2*M_PI ) horizAngle += 2*M_PI;

    updateViewMatrix();
}

void Player::updateViewMatrix(double xoff, double yoff) {
    vec3 direction = vec3( cos(vertAngle) * sin(horizAngle),  sin(vertAngle), cos(vertAngle) * cos(horizAngle) );        
    vec3 right     = vec3( sin(horizAngle - M_PI/2.0f),  0, cos(horizAngle - M_PI/2.0f) );    
    vec3 up        = glm::cross( right, direction );

    if ( yoff)
        position += direction * (float)yoff;

    if ( xoff)
        position += right * (float)xoff;
    //printf("player at (%f,%f,%f), horiz=%f, vert=%f\n", position.x, position.y, position.z, horizAngle, vertAngle);

    renderer->setView(glm::lookAt(  position,            // He's here
                                    position+direction, // and looks here : at the same position, plus "direction"
                                    up                  // Head is up (set to 0,-1,0 to look upside-down)
                           ));
    
    renderer->setCameraPosition(position);
    directionProjectionXoZ=vec2(direction.x,direction.z);
}
void Player::updatePosition(double xoff, double yoff) {
    updateViewMatrix(speed*xoff, speed*yoff);
}
