#include <algorithm>
#include "Renderer.h"
#include "Light.h"

Renderer::Renderer(mat4 P, mat4 V) :
    program("data/shaders/TransformVertexShader.vertexshader", "data/shaders/TextureFragmentShader.fragmentshader"),
    //program("data/shaders/laser/laser.vertexshader","data/shaders/laser/laser.fragmentshader")
    laserProgram("data/shaders/laser/laser.vertexshader","data/shaders/laser/laser.fragmentshader") {

    modelVertexHandle[0] = program.getAttrib("vertexPosition_modelspace");    
    vertexColorHandle[0] = program.getAttrib("vertexColor");
    textureSamplerHandle[0]  = program.getUniform("myTextureSampler");
    vertexUVHandle[0] = program.getAttrib("vertexUV");
    normalsHandle[0] = program.getAttrib("vertexNormal");

    modelVertexHandle[1] = laserProgram.getAttrib("vertexPosition_modelspace");    
    vertexColorHandle[1] = laserProgram.getAttrib("vertexColor");
    this->P = P; this->V = V; calculatePV();
}

void Renderer::setCurrentModelMatrix(mat4 M) {
    mat4 MVP = PV*M;
    program.setUniform("MVP", MVP);
    program.setUniform("M", M);
    program.setUniform("m_3x3_inv_transp", glm::transpose(glm::inverse(glm::mat3(M))));
    laserProgram.setUniform("MVP", MVP);
}

ShaderProgram* Renderer::getCurrentProgram() {
    return getActiveShader() == 1 ? &program : &laserProgram;
}

void Renderer::render(std::vector<Object*> objects) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    program.use();    
    program.setUniform("cameraPos", cameraPos);
    renderLights();
    for (int i = 0; i < objects.size(); i++) {
        if (objects.at(i)->needLaserShader()) {
            //printf("NEED LASER SHADER!");
            program.stopUsing();
            laserProgram.use();
            enableLaserShader();
            objects.at(i)->render(this);
            disableLaserShader();
            laserProgram.stopUsing();
            program.use();    
            program.setUniform("cameraPos", cameraPos);
            renderLights();
        } else {            
            if(objects.at(i)->hasLaserLight()) enableLaserLight(objects.at(i)->getLaserLight());
            objects.at(i)->render(this);
            disableLaserLight();
        }
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

/* TODO: Objects might have the laser hitting on them. enable laser light */
void Renderer::disableLaserLight() { program.setUniform("laserLightIndex", -1); }
void Renderer::enableLaserLight(Light* l) { sendLightToShader(31, l); program.setUniform("laserLightIndex", 31); }

void Renderer::sendLightToShader(int i, Light* light) {
    char buf[128];
    sprintf(buf, "lights[%d].position", i);
    program.setUniform(buf, light->getPosition());
    sprintf(buf, "lights[%d].intensities", i);
    program.setUniform(buf, light->getIntensities());
    sprintf(buf, "lights[%d].constantAttenuation", i);
    program.setUniform(buf, light->getConstantAttenuation());
    sprintf(buf, "lights[%d].linearAttenuation", i);
    program.setUniform(buf, light->getLinearAttenuation());
    sprintf(buf, "lights[%d].quadraticAttenuation", i);
    program.setUniform(buf, light->getQuadraticAttenuation());
}

void Renderer::renderLights() {
    static const int maxLights = 31; //FIXME: hardcoded we reserve 32 for the "laser light"

    int len = maxLights > lights.size() ? lights.size() : maxLights;
    program.setUniform("numUsedLights", len);
    for (int i = 0; i < len; i++) {
        sendLightToShader(i, lights.at(i));
    }

}
