#ifndef MODEL_H
#define MODEL_H

#include "ModelArrays.h"
#include "Texture.h"

//Forward declare the renderer
class Renderer ;

class Model
{
    private:
        ModelArrays* objectInfo; //FIXME: CHANGE THE NAME INTO SOMETHING MORE ADEQUATE
        Texture* texture;
        int primitiveType;

    public:
        Model(ModelArrays* info=NULL, Texture* text=NULL, int primitiveType = GL_TRIANGLES);
        virtual ~Model();

        // Call when entering rendering process
        virtual void beginRender(Renderer* renderer);

        // Call when we really ready to draw the model (i.e: has applied all textures, tranforms, etc)
        virtual void draw(Renderer* renderer);

        // Call when finishing the rendering process
        virtual void finishRender(Renderer* renderer);

        ModelArrays* getObjectInfo() { return this->objectInfo; }
        Texture*     getTexture()    { return this->texture; }

        virtual bool needLaserShader() { return false; }

    protected:
        void setPrimitiveType(int type) { this->primitiveType = type; }
        void setObjectInfo(ModelArrays* info) { this->objectInfo = info; }
};

#endif // MODEL_H
