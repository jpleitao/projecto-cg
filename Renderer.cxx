#include "Renderer.h"

Renderer::Renderer() :
    program("data/shaders/TransformVertexShader.vertexshader", "data/shaders/ColorFragmentShader.fragmentshader") {

    modelVertexHandle = program.getAttrib("vertexPosition_modelspace");    
    vertexColorHandle = program.getAttrib("vertexColor");
}

void Renderer::setCurrentModelMatrix(mat4 M) {
    mat4 MVP = PV*M;
    program.setUniform("MVP", MVP);
}

ShaderProgram* Renderer::getCurrentProgram() {
    return &program;
}

void Renderer::render(std::vector<Object*> objects) {
    for (int i = 0; i < objects.size(); i++) {
        objects.at(i)->render(this);
    }
}
