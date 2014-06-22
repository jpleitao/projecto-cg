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

    GLfloat lenght;
    GLfloat width;
    GLfloat height;
    GLfloat origin_lenght;
    GLfloat origin_width;
    GLfloat origin_height;

    GLfloat aceleration_y;
    GLfloat velocity_y;

    bool hasBoundingBox;

    //Hit box's stuff
    glm::vec4 center;
    glm::vec4 origin_center;
    std::vector<glm::vec4> vertexes;
    std::vector<glm::vec4> start_vertexes;

    public:
        Object(Model* model=NULL, Texture* texture=NULL, bool bound=false, GLfloat len=2, GLfloat w=2, GLfloat h=2, std::vector<glm::vec4> vert = std::vector<glm::vec4>());

        void rotate(GLfloat angle, vec3 axis);
        void scale(vec3 scaleVec);
        void translate(vec3 vec);
        void resetTransforms();
                
        virtual void render(Renderer* renderer);

        bool collision(Object* obj);
        void fall();
        void undoFall();

        GLfloat getCenterY(){return this->center[1];}
        GLfloat getHeight(){return this->height;}
        void setVelocity_y(GLfloat vel){this->velocity_y = vel;}

    private:
        void createHitBoxes();
        int ccw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3);
        int segmentIntersection(glm::vec4 a, glm::vec4 c, glm::vec4 b, glm::vec4 d);
        GLfloat area(glm::vec4 A, glm::vec4 B, glm::vec4 C);
        bool vertexInsideSquare(glm::vec4 point);
};
#endif // OBJECT_H
