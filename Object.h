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
    GLfloat obj_side;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> start_vertexes;

    public:
        Object(Model* model=NULL, Texture* texture=NULL, float side=2, std::vector<glm::vec3> vert = std::vector<glm::vec3>());

        void rotate(GLfloat angle, vec3 axis);
        void scale(vec3 scaleVec);
        void translate(vec3 vec);
        void resetTransforms();
                
        virtual void render(Renderer* renderer);

        bool collision(Object* obj);

        //REMOVE THIS
        void printStuff();

    private:
        void createHitBoxes();
        int ccw(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
        int segmentIntersection(glm::vec3 a, glm::vec3 c, glm::vec3 b, glm::vec3 d);
};
#endif // OBJECT_H
