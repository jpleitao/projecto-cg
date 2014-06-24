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

   float transparency;

    public:
        Object(Model* model=NULL, Texture* texture=NULL, bool bound=false, GLfloat len=2, GLfloat w=2, GLfloat h=2, std::vector<glm::vec4> vert = std::vector<glm::vec4>(), float transparency=1.0f);

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

        //DEBUG METHOD - REMOVE THIS
        void printStuff()
        {
            std::cout << "Length = " << this->lenght << " Width = " << this->width << " Height = " << this->height << std::endl;
            std::cout << "Center: (" << this->center[0] << "," << this->center[1] << "," << this->center[2] << ")\n";

            for (int i=0;i<this->vertexes.size();i++)
                std::cout << "Vertex " << i << ": (" << this->vertexes[i][0] << "," << this->vertexes[i][1] << "," << this->vertexes[i][2] << ")\n";
        }

        bool isTransparent() { return transparency < 1.0f; }

        bool needLaserShader() { return model ? model->needLaserShader() : false; }

    private:
        void createHitBoxes();
        GLfloat ccw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3);
        int segmentIntersection(glm::vec4 a, glm::vec4 c, glm::vec4 b, glm::vec4 d);
        bool pointInLine(vec4 a, vec4 b, vec4 point);
        int pointInTriangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::vec4 pt);

};
#endif // OBJECT_H
