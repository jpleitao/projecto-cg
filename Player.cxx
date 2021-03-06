#include "Player.h"
#include "common.h"

Player::Player(Renderer* renderer, vec3 position, float horizAngle, float vertAngle, float fov, float speed, float mouseSpeed) :
    renderer(renderer), position(position), horizAngle(horizAngle), vertAngle(vertAngle), fov(fov), speed(speed), mouseSpeed(mouseSpeed) {
        updateViewMatrix();

        //Initialize hit box based on current player's positions
        this->createHitBox();
}

void Player::createHitBox()
{
    this->hit_box = std::vector<glm::vec4>();

    this->hit_box.push_back(glm::vec4(this->position[0], 0.0f, this->position[2] + PLAYER_BOX_WIDTH/2, 1.0f));
    this->hit_box.push_back(glm::vec4(this->position[0], this->position[1], this->position[2] + PLAYER_BOX_WIDTH/2, 1.0f));
    this->hit_box.push_back(glm::vec4(this->position[0], this->position[1], this->position[2] - PLAYER_BOX_WIDTH/2, 1.0f));
    this->hit_box.push_back(glm::vec4(this->position[0], 0.0f, this->position[2] - PLAYER_BOX_WIDTH/2, 1.0f));
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
    glm::vec3 old = this->position;
    updateViewMatrix(speed*xoff, speed*yoff);
    glm::vec3 new_pos = this->position;
    glm::vec3 vec = new_pos - old;

    this->createHitBox();
}

void Player::updatePosition(vec3 position)
{
    this->setPosition(position);


    this->createHitBox();
}

//Same code as Object::collisions, but adapted. Don't have the time or patience to port it to ObjectManager. Deal with it
bool Player::colideWithObject(Object* obj)
{
    if(!obj->objectHasBoundingBox())
        return false;

    //"Obj" is higher than our player
    if ((obj->getCenterY() - obj->getHeight()/2) > this->position[1])
        return false;

    glm::vec4 a, b, c, d;
    int current_size, obj_size;

    current_size = this->hit_box.size();
    obj_size = obj->getVertexesSize();

    if ( (current_size != 4) || (obj_size != 4) )
        assert(0);//We can only have squares/rectangles!

    //Same dimensions
    for (int i=0;i<current_size;i++){
        a = this->hit_box[i];
        b = this->hit_box[(i+1)%current_size];

        a[0] = a[0] + 0.001;
        a[2] = a[2] + 0.001;
        b[0] = b[0] + 0.001;
        b[2] = b[2] + 0.001;

        for (int j=0;j<obj_size;j++){
            c = obj->getVertexAt(j);
            d = obj->getVertexAt((j+1)%obj_size);

            if (obj->segmentIntersection(a,c,b,d))
                return true;
        }
    }

    GLfloat current_area, obj_area;

    current_area = PLAYER_BOX_WIDTH * PLAYER_BOX_WIDTH;
    obj_area = obj->getArea();

    //Different Dimensions -- One can be inside the other (The one with smaller area inside the one with higher area)
    if ( current_area < obj_area){
        //player inside obj

        for (int i=0;i<current_size;i++){
            //First triangle: 0, 1 and 2
            if(obj->pointInTriangle(obj->getVertexAt(0), obj->getVertexAt(1), obj->getVertexAt(2), this->hit_box[i]))
                return true;
            
            //Second triangle: 0,3 and 2
            if(obj->pointInTriangle(obj->getVertexAt(0), obj->getVertexAt(3), obj->getVertexAt(2), this->hit_box[i]))
                return true;

            //Test if the point is in the line of the triangles -- Line that has the points 0 and 2
            if (obj->pointInLine(obj->getVertexAt(0), obj->getVertexAt(2), this->hit_box[i]))
                return true;
        }
    }

    else if (obj_area < current_area){
        //obj inside player

        for (int i=0;i<obj_size;i++){
            if (obj->pointInTriangle(this->hit_box[0], this->hit_box[1], this->hit_box[2], obj->getVertexAt(i)))
                return true;

            if(obj->pointInTriangle(this->hit_box[0], this->hit_box[3], this->hit_box[2], obj->getVertexAt(i)))
                return true;

            //Test if the point is in the line of the triangles -- Line that has the points 0 and 2
            if (obj->pointInLine(this->hit_box[0], this->hit_box[2], obj->getVertexAt(i)))
                return true;
        }
    }

    return false;
}
