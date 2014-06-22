#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "common.h"
#include "shaders/ShaderProgram.h"
#include "Object.h"

class Light;

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
    
    GLint textureSamplerHandle;

    GLint vertexUVHandle;

    GLint normalsHandle;

    //FIXME: Might add other handles   
    std::vector<Light*> lights; 

    vec3 cameraPos;

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

        void setCameraPosition(vec3 pos) { this->cameraPos = pos; }
        
        GLint getModelVertexHandle()    { return modelVertexHandle; }
        GLint getVertexColorHandle()    { return vertexColorHandle; }
        GLint getTextureSamplerHandle() { return textureSamplerHandle; }
        GLint getVertexUVHandle()       { return vertexUVHandle; }
        GLint getNormalsHandle()       { return normalsHandle; }

        void render(std::vector<Object*> objects);

        ShaderProgram* getCurrentProgram();

        void removeLight(Light* light);
        void addLight(Light* light);

    private:
        void calculatePV() { PV = P * V; }

        void renderLights();

};

#endif // RENDERER_H
