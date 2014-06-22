#include "Object.h"
#include "Renderer.h"

Object::Object(Model* model, Texture* texture, bool bound, GLfloat len, GLfloat w, GLfloat h, std::vector<glm::vec4> vert) : model(model), texture(texture), modelMatrix(mat4(1.0f))
{
    this->hasBoundingBox = bound;

    this->lenght = len;
    this->width = w;
    this->height = h;
    
    this->origin_center = glm::vec4(0,0,0,1);//The cube is centered in the origin
    this->center = this->origin_center;
    this->vertexes = vert;
    this->start_vertexes = vert;
}

//CCW -- Taken from DNP@LPA
int Object::ccw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3) {
    /*p2->x * p3->y + p1->x * p2->y + p1->y * p3->x - p1->y * p2->x - p1->x * p3->y - p2->y * p3->x
     *Remeber that here we only have x and z!
     */
    return p2[0] * p3[2] + p1[0] * p2[2] + p1[2] * p3[0] - p1[2] * p2[0] - p1[0] * p3[2] - p2[2] * p3[0] > 0 ? 1 : -1;
}

//Segment intersection -- Taken from DNP@LPA -- Checks if |AB| intersects |CD|
int Object::segmentIntersection(glm::vec4 a, glm::vec4 c, glm::vec4 b, glm::vec4 d) {
    return ccw(a,c,d) != ccw(b,c,d) && ccw(a,b,c) != ccw(a,b,d);
}

bool Object::collision(Object* obj)
{
    if (!this->hasBoundingBox || !obj->hasBoundingBox)
        return false;

    //If the current object is under the first one then we have no collision
    std::cout << (this->center[1] + (this->height/2)) << " < " << (obj->center[1] - (obj->height/2)) << std::endl;
    if ( (this->center[1] + (this->height/2)) < (obj->center[1] - (obj->height/2)) ){
        std::cout << "AQUI\n";
        return false;
    }

    //If the current object is above the first one then we have no collision
    std::cout << (this->center[1] - (this->height/2)) << " > " << (obj->center[1] + (obj->height/2)) << std::endl;
    if ( (this->center[1] - (this->height/2)) > (obj->center[1] + (obj->height/2)) ){
        std::cout << "AQUI2\n";
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
            //j and (j+1)%4
            c = obj->vertexes[j];
            d = obj->vertexes[(j+1)%obj_size];

            if (this->segmentIntersection(a,c,b,d)){
                std::cout << "Found collision! Going to return true" << std::endl;
                if (this->center[1] > obj->center[1])
                    std::cout << "I am the one on top of the other!" << std::endl;
                return true;
            }
        }
    }

    float current_area, obj_area;

    current_area = this->lenght * this->width;
    obj_area = obj->lenght * obj->width;

    //Different Dimensions -- One can be inside the other (The one with smaller area inside the one with higher area)
    if ( current_area < obj_area){
        //current inside obj
        for (int i=0;i<this->vertexes.size();i++){
            if (obj->vertexInsideSquare(this->vertexes[i]))
                return true;
        }
    }

    else if (obj_area < current_area){
        //obj inside current
        for (int i=0;i<obj->vertexes.size();i++){
            if (this->vertexInsideSquare(obj->vertexes[i]))
                return true;
        }
    }

    std::cout << "NOPE\n";

    return false;
}

GLfloat Object::area(glm::vec4 A, glm::vec4 B, glm::vec4 C)
{
    return (C[0]*B[2]-B[0]*C[2])-(C[0]*A[2]-A[0]*C[2])+(B[0]*A[2]-A[0]*B[2]);
}

bool Object::vertexInsideSquare(glm::vec4 point)
{
    if (this->area(this->vertexes[0],this->vertexes[1],point)>0 || this->area(this->vertexes[1],this->vertexes[2],point)>0 ||
        this->area(this->vertexes[2],this->vertexes[3],point)>0 || this->area(this->vertexes[3],this->vertexes[0],point)>0)
        return false;

    return true;
}

void Object::rotate(GLfloat angle, vec3 axis) {
    this->modelMatrix = glm::rotate(modelMatrix, angle, axis);

    //Update the object's vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];
}

void Object::scale(vec3 scaleVec) {
    this->modelMatrix = glm::scale(modelMatrix, scaleVec);

    //Update the object's center position
    this->center = this->modelMatrix * this->origin_center;

    //Update the vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];;
}

void Object::translate(vec3 vec) {
    this->modelMatrix = glm::translate(modelMatrix, vec);

    //Update the object's center position and vertexes' coordinates
    this->center = this->modelMatrix * this->origin_center;

    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = this->modelMatrix * this->start_vertexes[i];
}

void Object::resetTransforms() {   
    //Turn modelMatrix into the identity matrix 
    this->modelMatrix = mat4(1.0f);

    //Reset center and vertexes' positions
    this->center = this->origin_center;
    this->vertexes = this->start_vertexes;
}

void Object::render(Renderer* renderer) {

    //Update MVP
    renderer->setCurrentModelMatrix(modelMatrix);    

    //Draw the model with the texture mapped
    texture->beginRender(renderer, model);
    model->beginRender(renderer);

    model->draw(renderer);
    
    model->finishRender(renderer);
    texture->finishRender(renderer, model);
}
