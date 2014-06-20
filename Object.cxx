#include "Object.h"
#include "Renderer.h"

Object::Object(Model* model, Texture* texture, int side, std::vector<glm::vec3> vert) : model(model), texture(texture), modelMatrix(mat4(1.0f))
{
    this->my_side = side;
    this->center = glm::vec3(0,0,0);//The cube is centered in the origin
    this->vertexes = vert;
    this->start_vertexes = vert;
}

void Object::rotate(GLfloat angle, vec3 axis) {
    this->modelMatrix = glm::rotate(modelMatrix, angle, axis);

    //FIXME: DO THIS!
}

void Object::scale(vec3 scaleVec) {
    this->modelMatrix = glm::scale(modelMatrix, scaleVec);

    //Update the object's center position
    for(int i=0;i<3;i++)
        this->center[i] *= scaleVec[i];

    for (int i=0;i<this->vertexes.size();i++){
        for (int j=0;j<3;j++)
            this->vertexes[i][j] *= scaleVec[j];
    }

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

    //Update MVC
    renderer->setCurrentModelMatrix(modelMatrix);    

    //Draw the model with the texture mapped
    texture->beginRender(renderer, model);
    model->beginRender(renderer);

    model->draw(renderer);
    
    model->finishRender(renderer);
    texture->finishRender(renderer, model);
}
