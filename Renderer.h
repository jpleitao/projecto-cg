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
        Renderer();

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
