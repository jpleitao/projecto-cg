#include "Renderer.h"
#include "Light.h"

Renderer::Renderer(mat4 P, mat4 V) :
    program("data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader") {

    modelVertexHandle = program.getAttrib("vertexPosition_modelspace");    
    vertexColorHandle = program.getAttrib("vertexColor");
    textureSamplerHandle  = program.getUniform("myTextureSampler");
    vertexUVHandle = program.getAttrib("vertexUV");
    normalsHandle = program.getAttrib("vertexNormal");
    this->P = P; this->V = V; calculatePV();
}

void Renderer::setCurrentModelMatrix(mat4 M) {
    mat4 MVP = PV*M;
    program.setUniform("MVP", MVP);
    program.setUniform("M", M);
    program.setUniform("m_3x3_inv_transp", glm::transpose(glm::inverse(glm::mat3(M))));
     
}

ShaderProgram* Renderer::getCurrentProgram() {
    return &program;
}

void Renderer::render(std::vector<Object*> objects) {
    program.use();

    program.setUniform("cameraPos", cameraPos);
    renderLights();
    for (int i = 0; i < objects.size(); i++) {
            
        objects.at(i)->render(this);
    }
    program.stopUsing();
}

void Renderer::removeLight(Light* light) {

    std::vector<Light*>::iterator position = std::find(lights.begin(), lights.end(), light);
    if (position != lights.end())
        lights.erase(position);
    light->setRenderer(NULL);
}

void Renderer::addLight(Light* light) {
    lights.push_back(light);
    light->setRenderer(this);
}

void Renderer::renderLights() {
    static const int maxLights = 32; //FIXME: hardcoded

    int len = maxLights > lights.size() ? lights.size() : maxLights;
    program.setUniform("numUsedLights", len);
    for (int i = 0; i < len; i++) {
        char buf[128];
        sprintf(buf, "lights[%d].position", i);
        program.setUniform(buf, lights.at(i)->getPosition());
        sprintf(buf, "lights[%d].intensities", i);
        program.setUniform(buf, lights.at(i)->getIntensities());
        sprintf(buf, "lights[%d].constantAttenuation", i);
        program.setUniform(buf, lights.at(i)->getConstantAttenuation());
        sprintf(buf, "lights[%d].linearAttenuation", i);
        program.setUniform(buf, lights.at(i)->getLinearAttenuation());
        sprintf(buf, "lights[%d].quadraticAttenuation", i);
        program.setUniform(buf, lights.at(i)->getQuadraticAttenuation());
    }

}
