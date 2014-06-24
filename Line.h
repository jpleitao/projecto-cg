#ifndef LINE_H
#define LINE_H
#include "Model.h"
#include <vector>

class Line : public Model
{
    private:
        std::vector<vec3> colors;
        GLuint colorBuffer;
    public:
        //FIXME: Hardcoded values
        Line(vec3 start=vec3(0,2,-20), vec3 end=vec3(0,2,20), vec3 color=vec3(1,0,0)) : Model(NULL,NULL,GL_LINES) {

            std::vector<vec3> vertex;
            vertex.push_back(start); vertex.push_back(end);
            colors.push_back(color);colors.push_back(color);

            ModelArrays* arrays = new ModelArrays(vertex, std::vector<glm::vec2>(), std::vector<glm::vec3>());
            setObjectInfo(arrays);

            glGenBuffers(1, &this->colorBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
            glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
        } 

        virtual void beginRender(Renderer* renderer) {
            Model::beginRender(renderer);

            glEnableVertexAttribArray(renderer->getVertexColorHandle());
            glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
            glVertexAttribPointer(
                renderer->getVertexColorHandle(),               // The attribute we want to configure
                3,                           // size
                GL_FLOAT,                    // type
                GL_FALSE,                    // normalized?
                0,                           // stride
                (void*)0                     // array buffer offset
            );

        }

        virtual void draw(Renderer* renderer) {
            printf("Line drawing!\n");

            Model::draw(renderer);

        }
        virtual void finishRender(Renderer* renderer) {
            glDisableVertexAttribArray(renderer->getVertexColorHandle());
            Model::finishRender(renderer);
        }

        virtual bool needLaserShader() { return true; }
};

#endif // MODEL_H
