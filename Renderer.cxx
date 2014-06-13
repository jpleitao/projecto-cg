#include "Renderer.h"

Renderer::Renderer(mat4 P, mat4 V) :
    program("data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader") {

    modelVertexHandle = program.getAttrib("vertexPosition_modelspace");    
    vertexColorHandle = program.getAttrib("vertexColor");
    textureSamplerHandle  = program.getUniform("myTextureSampler");
    vertexUVHandle = program.getAttrib("vertexUV");
    this->P = P; this->V = V; calculatePV();
}

void Renderer::setCurrentModelMatrix(mat4 M) {
    mat4 MVP = PV*M;
    program.setUniform("MVP", MVP);
}

ShaderProgram* Renderer::getCurrentProgram() {
    return &program;
}

void Renderer::render(std::vector<Object*> objects) {
    program.use();
    for (int i = 0; i < objects.size(); i++) {
            
        objects.at(i)->render(this);
    }
    program.stopUsing();
}
