#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "Model.h"
#include "shaders/ShaderProgram.h"

class Renderer; //Forward declare Renderer

class Object
{
    Model* model;
    Texture* texture;

    //Matrix we pass to the shaders
    glm::mat4 modelMatrix;

    //Hit box's stuff
    glm::vec3 center;
    int my_side;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> start_vertexes;

    public:
        Object(Model* model=NULL, Texture* texture=NULL, int side=2, std::vector<glm::vec3> vert = std::vector<glm::vec3>());

        void rotate(GLfloat angle, vec3 axis);
        void scale(vec3 scaleVec);
        void translate(vec3 vec);
        void resetTransforms();
                
        virtual void render(Renderer* renderer);

    private:
        void createHitBoxes();
};

#endif // OBJECT_H
