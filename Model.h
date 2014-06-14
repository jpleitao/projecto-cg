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

    public:
        Model(ModelArrays* info=NULL, Texture* text=NULL);
        ~Model();

        // Call when entering rendering process
        void beginRender(Renderer* renderer);

        // Call when we really ready to draw the model (i.e: has applied all textures, tranforms, etc)
        void draw(Renderer* renderer);

        // Call when finishing the rendering process
        void finishRender(Renderer* renderer);

        ModelArrays* getObjectInfo() { return this->objectInfo; }
        Texture*     getTexture()    { return this->texture; }
};

#endif // MODEL_H
