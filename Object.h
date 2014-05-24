#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "Model.h"
#include "shaders/ShaderProgram.h"

class Object
{
    Model* model;

    //Matrix we pass to the shaders
    glm::mat4 modelMatrix;

    public:
        Object(Model* model=NULL);    

        void rotate(GLfloat angle, vec3 axis);
        void scale(vec3 scaleVec);
        void translate(vec3 vec);
        void resetTransforms();
        
        //Render this object using this program shader
        virtual void render(ShaderProgram program);
};

#endif // OBJECT_H
