#include "Object.h"
#include "Renderer.h"
#include "Light.h"

Object::Object(Model* model, Texture* texture, bool bound, GLfloat len, GLfloat w, GLfloat h, std::vector<glm::vec4> vert, float transparency) : model(model), texture(texture), modelMatrix(mat4(1.0f)), transparency(transparency)
{
    this->hasBoundingBox = bound;
    this->isBeingPuxed = false;
    
    this->velocity = vec3(0.0f, 0.0f, 0.0f);

    this->origin_lenght = len;
    this->origin_width = w;
    this->origin_height = h;

    this->lenght = len;
    this->width = w;
    this->height = h;

    this->has_last_position = false;

    this->aceleration_y = OBJ_ACELERATION;//FIXME: HARD-CODED VALUE

    this->origin_center = glm::vec4(0,0,0,1);//The cube is centered in the origin
    this->center = this->origin_center;
    this->vertexes = vert;
    this->start_vertexes = vert;
    this->rotate(1,vec3(0,1,0));
    this->rotate(-1,vec3(0,1,0));
    laserLight = NULL;
}

Object::~Object() {
    //FIXME: Hacky way to free up line resources
    if ( this->model && this->model->needLaserShader()) delete model;

    if ( this->laserLight ) delete laserLight;
}

void Object::updatePlayerLastPosition()
{
    //We are going to move the object, so lets update its center's last position
    this->has_last_position = true;
    this->last_position = this->center;
}

void Object::fall()
{
    //Update object's velocity, based on its aceleration
    this->velocity[1] += this->aceleration_y;

    //Update the player's last position
    this->updatePlayerLastPosition();

    //Move the object according to its velocity
    this->translate(vec3(0.0f, this->velocity[1], 0.0f));

    //Check if on the floor
    if (this->center[1] < (this->height/2) ){
        this->translate(vec3(0.0f, -this->velocity[1] , 0.0f));
        this->velocity[1] = 0;
    }
}

void Object::undoFall()
{
    //Move the object up, in the opposite direction of the last "fall" (due to gravity)
    this->translate(vec3(0.0f, -this->velocity[1], 0.0f));
}

//CCW -- Taken from DNP@LPA
GLfloat Object::ccw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    /*p2->x * p3->y + p1->x * p2->y + p1->y * p3->x - p1->y * p2->x - p1->x * p3->y - p2->y * p3->x
     *Remeber that here we only have x and z!
     */
    return p2[0] * p3[2] + p1[0] * p2[2] + p1[2] * p3[0] - p1[2] * p2[0] - p1[0] * p3[2] - p2[2] * p3[0] > 0 ? 1 : -1;
}

//Segment intersection -- Taken from DNP@LPA -- Checks if |AB| intersects |CD|
int Object::segmentIntersection(glm::vec4 a, glm::vec4 c, glm::vec4 b, glm::vec4 d) {
    return ccw(a,c,d) != ccw(b,c,d) && ccw(a,b,c) != ccw(a,b,d);
}


//Point in triangle -- Taken from DNP@LPA
int Object::pointInTriangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::vec4 pt)
{
    GLfloat b1, b2, b3;

    b1 = ccw(pt, v1, v2);
    b2 = ccw(pt, v2, v3);
    b3 = ccw(pt, v3, v1);

    return ((b1 == b2) && (b2 == b3));
}

//Returns true if "point" is in the line segment formed by "a" and "b"
//This function appear to be working well
bool Object::pointInLine(vec4 a, vec4 b, vec4 point)
{
    GLfloat m = (b[2] - a[2]) / (b[0] - a[0]);

    //We know that a is a point of the segment
    GLfloat origin = a[2] - (m * a[0]);//y = mx + b <=> b = y - mx

    //Here we know the equation of the line segment: y = m*x + b, so lets see if the point is in the segment
    GLfloat y_final = m*point[0] + origin;

    //std::cout << y_final << " == " << point[2] << std::endl;

    if (y_final == point[2])
        return true;

    return false;
}

bool Object::collision(Object* obj)
{
    if (!this->hasBoundingBox || !obj->hasBoundingBox)
        return false;

    //If the current object is under the first one then we have no collision
    //std::cout << (this->center[1] + (this->height/2)) << " < " << (obj->center[1] - (obj->height/2)) << std::endl;
    if ( (this->center[1] + (this->height/2)) < (obj->center[1] - (obj->height/2)) ){
        //std::cout << "AQUI\n";
        return false;
    }

    //If the current object is above the first one then we have no collision
    //std::cout << (this->center[1] - (this->height/2)) << " > " << (obj->center[1] + (obj->height/2)) << std::endl;
    if ( (this->center[1] - (this->height/2)) > (obj->center[1] + (obj->height/2)) ){
        //std::cout << "AQUI2\n"; FARTO DESTES PRINTS DE MERDA
        return false;
    }

    /*If their heights "interset each other" then we have to solve the collision in 2D
     *This is how I am planning on doing this:
     *We have 2 squares and we want to know if they collide with each other. If they have the same dimensions, for each edge of
     *one square we are going to se if it intersects the edges of the other square. If there is at least one intersection then
     *we have a collision!
     */

    glm::vec4 a, b, c, d;
    int current_size, obj_size;

    current_size = this->vertexes.size();
    obj_size = obj->vertexes.size();

    if ( (current_size != 4) || (obj_size != 4) )
        assert(0);//FIXME?? We can only have squares/rectangles!

    //Same dimensions
    for (int i=0;i<current_size;i++){
        //i and (i+1)%4
        a = this->vertexes[i];
        b = this->vertexes[(i+1)%current_size];

        /*This is my hack. Now, why did I did this here? Suppose that we have one box on top of the other (The down face of one box
         *is perfectly on top of the upper face of the other). In this situation, if we consider only our 2D approach here (X and
         *Z coordinates) we have two overlaping squares. This shouldn't be a problem, since we are obtaining the intersections and
         *all. However, I am 90% sure this is a problem caused because of our limited precision with floats. So, we add a small
         *value to one of our squares edges, forcing the intersection in this situation. I see one problem with this "solution":
         *We are adding a positive increment to the X and Z coordinates of the two edges of the "this" instance of the Object
         *class (my english here was terrible, sorry about that but it's 0am on a June Sunday xD), and as a consequence of that
         *we may be making some situations where we should have a collision no longer be a collision. I think that the problem of
         *not detecting the collision of 2 boxes, one on top of the other, is more important than not detecting two boxes colliding
         *only on 1 milimeter or centimiter, but I am open to a discussion on this matter ;)*/
        a[0] = a[0] + 0.001;
        a[2] = a[2] + 0.001;
        b[0] = b[0] + 0.001;
        b[2] = b[2] + 0.001;

        for (int j=0;j<obj_size;j++){
            c = obj->vertexes[j];
            d = obj->vertexes[(j+1)%obj_size];

            if (this->segmentIntersection(a,c,b,d)){
                std::cout << "Found collision! Going to return true" << std::endl;

                /*if (this->center[1] > obj->center[1]){
                    //std::cout << "I am the one on top of the other!" << std::endl;
                }*/
                return true;
            }
        }
    }

    GLfloat current_area, obj_area;

    current_area = this->lenght * this->width;
    obj_area = obj->lenght * obj->width;

    //std::cout << "Current_area = " << current_area << " Obj_area = " << obj_area << std::endl;

    //Different Dimensions -- One can be inside the other (The one with smaller area inside the one with higher area)
    if ( current_area < obj_area){
        //current inside obj
        //std::cout << "MENOR\n";

        for (int i=0;i<obj->vertexes.size();i++){
            //First triangle: 0, 1 and 2
            if(this->pointInTriangle(obj->vertexes[0], obj->vertexes[1], obj->vertexes[2], this->vertexes[i])){
                //std::cout << "AQUI3\n";
                return true;
            }
            //Second triangle: 0,3 and 2
            if(this->pointInTriangle(obj->vertexes[0], obj->vertexes[3], obj->vertexes[2], this->vertexes[i])){
                //std::cout << "AQUI4\n";
                return true;
            }

            //Test if the point is in the line of the triangles -- Line that has the points 0 and 2
            if (this->pointInLine(obj->vertexes[0], obj->vertexes[2], this->vertexes[i])){
                //std::cout << "AQUI5\n";
                return true;
            }
        }
    }

    else if (obj_area < current_area){
        //obj inside current

        //std::cout << "MAIOR\n";

        for (int i=0;i<this->vertexes.size();i++){
            if (this->pointInTriangle(this->vertexes[0], this->vertexes[1], this->vertexes[2], obj->vertexes[i])){
                //std::cout << "AQUI6\n";
                return true;
            }

            if(pointInTriangle(this->vertexes[0], this->vertexes[3], this->vertexes[2], obj->vertexes[i])){
                //std::cout << "AQUI7\n";
                return true;
            }

            //Test if the point is in the line of the triangles -- Line that has the points 0 and 2
            if (this->pointInLine(this->vertexes[0], this->vertexes[2], obj->vertexes[i])){
                //std::cout << "AQUI8\n";
                return true;
            }
        }
    }

    //std::cout << "NOPE\n";

    return false;
}

//Slowly move the "this" object away from "obj" in the direction of "obj's" velocity
void Object::moveAwayFrom(Object* obj, glm::vec4 movement)
{
    vec3 del = vec3(FACTOR*movement[0],0.0f,FACTOR*movement[2]);
    //Move the object away
    while(this->collision(obj)){
        this->translate(del);
        
        //Update the player's last position
        this->updatePlayerLastPosition();
        
        //std::cout << "Moving this away from obj\n";
    }
}

//Method to handle the object's collisions. If value = true then the player is hiting the object and it should be moving
void Object::move(bool value, GLfloat vx, GLfloat vz)
{
    //Make the object be moving
    this->isBeingPuxed = value;

    //Update the object's velocity
    this->velocity[0] = vx;
    this->velocity[2] = vz;
}

void Object::rotate(GLfloat angle, vec3 axis) {
    if (angle == 0)
        return ;

    this->modelMatrix = glm::rotate(modelMatrix, angle, axis);

    //Update the object's vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];

    //Update the player's last position
    this->updatePlayerLastPosition();
}

void Object::scale(vec3 scaleVec) {
    this->modelMatrix = glm::scale(modelMatrix, scaleVec);

    //Update the object's center position
    this->center = this->modelMatrix * this->origin_center;

    //Update the vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];

    //Update the object's lenght, width and height
    this->width = sqrt( (this->vertexes[0][0]-this->vertexes[1][0]) * (this->vertexes[0][0]-this->vertexes[1][0]) +
                        (this->vertexes[0][1]-this->vertexes[1][1]) * (this->vertexes[0][1]-this->vertexes[1][1]) +
                        (this->vertexes[0][2]-this->vertexes[1][2]) * (this->vertexes[0][2]-this->vertexes[1][2]) );
    this->lenght = this->width;
    this->height *= scaleVec[1];

    //Update the player's last position
    this->updatePlayerLastPosition();
}

void Object::translate(vec3 vec) {
    this->modelMatrix = glm::translate(modelMatrix, vec);

    //Update the object's center position and vertexes' coordinates
    this->center = this->modelMatrix * this->origin_center;

    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];

    //Update the player's last position
    this->updatePlayerLastPosition();
}

void Object::resetTransforms() {
    //Turn modelMatrix into the identity matrix
    this->modelMatrix = mat4(1.0f);

    //Reset center and vertexes' positions
    this->center = this->origin_center;
    this->vertexes = this->start_vertexes;

    //Reset lenght, width and height
    this->lenght = this->origin_lenght;
    this->width = this->origin_width;
    this->height = this->origin_height;

    //Update the player's last position
    this->has_last_position = false;
}

void Object::render(Renderer* renderer) {
    printf("DRawing object. Alpha: %f\n", transparency);
    //Update MVP
    renderer->setCurrentModelMatrix(modelMatrix);

    //Draw the model with the texture mapped
    if ( texture ) texture->beginRender(renderer, model);
    model->beginRender(renderer);

    renderer->getCurrentProgram()->setUniform("objectAlpha", this->transparency);

    model->draw(renderer);

    model->finishRender(renderer);
    if ( texture ) texture->finishRender(renderer, model);
}

void Object::setLaserLight(Light* l) { if(laserLight) delete laserLight; laserLight = l; }

std::vector<std::vector<vec2> > Object::getBoundingBoxLines() {
    std::vector<std::vector<vec2> > ret;
    for (int i=0;i<this->vertexes.size();i++){
        //i and (i+1)%4
        std::vector<vec2> line;
        line.push_back ( vec2(this->vertexes[i].x,this->vertexes[i].z ) );
        vec4 v = this->vertexes[(i+1)%this->vertexes.size()];
        line.push_back ( vec2(v.x,v.z) );

        ret.push_back(line);
    }

    return ret;
}
