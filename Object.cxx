#include "Object.h"
#include "Renderer.h"

Object::Object(Model* model, Texture* texture, float side, std::vector<glm::vec3> vert) : model(model), texture(texture), modelMatrix(mat4(1.0f))
{
    this->obj_side = side;
    this->center = glm::vec3(0,0,0);//The cube is centered in the origin
    this->vertexes = vert;
    this->start_vertexes = vert;
}

void Object::rotate(GLfloat angle, vec3 axis) {
    this->modelMatrix = glm::rotate(modelMatrix, angle, axis);

    //Get the rotation matrix
    glm::mat4 rotation_matrix = glm::rotate(mat4(1.0f), angle, axis);

    //Update the center's position
    this->center = glm::vec3(rotation_matrix * glm::vec4(this->center, 0.0f));

    //Update the object's vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] = glm::vec3(rotation_matrix * glm::vec4(this->vertexes[i], 0.0f));
}

//CCW -- Taken from DNP@LPA
int Object::ccw(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    /*p2->x * p3->y + p1->x * p2->y + p1->y * p3->x - p1->y * p2->x - p1->x * p3->y - p2->y * p3->x
     *Remeber that here we only have x and z!
     */
    return p2[0] * p3[2] + p1[0] * p2[2] + p1[2] * p3[0] - p1[2] * p2[0] - p1[0] * p3[2] - p2[2] * p3[0] > 0 ? 1 : -1;
}

//Segment intersection -- Taken from DNP@LPA -- Checks if |AB| intersects |CD|
int Object::segmentIntersection(glm::vec3 a, glm::vec3 c, glm::vec3 b, glm::vec3 d) {
    return ccw(a,c,d) != ccw(b,c,d) && ccw(a,b,c) != ccw(a,b,d);
}

bool Object::collision(Object* obj)
{
    //If the current object is under the first one then we have no collision
    if ( (this->center[1] + this->obj_side) < (obj->center[1] - obj->obj_side) )
        return false;

    //If the current object is above the first one then we have no collision
    if ( (this->center[1] - this->obj_side) > (obj->center[1] + obj->obj_side) )
        return false;

    /*If their heights "interset each other" then we have to solve the collision in 2D
     *This is how I am planning on doing this:
     *We have 2 squares and we want to know if they collide with each other. Since they have the same dimensions we cannot have
     *one square inside the other, so what we are going to do is, for each edge of one square we are going to se if it intersects
     *the edges of the other square. If there is at least one intersection then we have a collision!
     */

    glm::vec3 a, b, c, d;
    int current_size, obj_size;

    current_size = this->vertexes.size();
    obj_size = obj->vertexes.size();

    if ( (current_size != 4) || (obj_size != 4) )
        assert(0);//FIXME?? We can only have squares right?

    for (int i=0;i<current_size;i++){
        //i and (i+1)%4
        a = this->vertexes[i];
        b = this->vertexes[(i+1)%current_size];

        for (int j=0;j<obj_size;j++){
            //j and (j+1)%4
            c = obj->vertexes[j];
            d = obj->vertexes[(j+1)%obj_size];

            if (this->segmentIntersection(a,c,b,d))
                return true;
        }
    }

    return false;
}

//Remove this
void Object::printStuff()
{
    std::cout << "Center = ("<< this->center[0] << "," << this->center[1] << "," << this->center[2] << ")\n";

    for (int i=0;i<this->vertexes.size();i++)
        std::cout << "Vertex " << i << " = (" << this->vertexes[i][0] << "," << this->vertexes[i][1] << "," << this->vertexes[i][2] <<")\n";
}

void Object::scale(vec3 scaleVec) {
    this->modelMatrix = glm::scale(modelMatrix, scaleVec);

    //Update the object's center position
    this->center *= scaleVec;
    //Update the vertexes' position
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] *= scaleVec;
}

void Object::translate(vec3 vec) {
    this->modelMatrix = glm::translate(modelMatrix, vec);

    //Update the object's center position and vertexes' coordinates
    this->center += vec;
    for (int i=0;i<this->vertexes.size();i++)
        this->vertexes[i] += vec;
}

void Object::resetTransforms() {   
    //Turn modelMatrix into the identity matrix 
    this->modelMatrix = mat4(1.0f);

    //Reset center and vertexes' positions
    this->center = glm::vec3(0,0,0);
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
