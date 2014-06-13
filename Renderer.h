#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "common.h"
#include "shaders/ShaderProgram.h"
#include "Object.h"

class Renderer
{
    private:

    // PV Matrix, calculated from the matrixes below, but stored here for efficiency
    mat4 PV;

    // Projection and View. PV is just P*V
    mat4 P, V;
    
    // The only shader we currently use
    ShaderProgram program;

    // Handle to where we should store the array of vertexes
    GLint modelVertexHandle;

    // Handle to where we should store the array of vertex colors (FIXME: Might be gone soon)
    GLint vertexColorHandle;

    //FIXME: Might add other handles    

    public:
        Renderer(mat4 P = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f),
                mat4 V       = glm::lookAt(
                                vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
                                vec3(0,0,0), // and looks at the origin
                                vec3(0,1,0))  // Head is up (set to 0,-1,0 to look upside-down)
        );

        void setProjection(mat4 P) { this->P = P; calculatePV();}
        void setView(mat4 V) { this->V = V; calculatePV();}
        void setCurrentModelMatrix(mat4 M);
        
        GLint getModelVertexHandle() { return modelVertexHandle; }
        GLint getVertexColorHandle() { return vertexColorHandle; }

        void render(std::vector<Object*> objects);

        ShaderProgram* getCurrentProgram();

    private:
        void calculatePV() { PV = P * V; }

};

#endif // RENDERER_H
