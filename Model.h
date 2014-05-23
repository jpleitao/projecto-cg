#ifndef MODEL_H
#define MODEL_H

#include "ModelArrays.h"
#include "Texture.h"

class Model
{
    private:
        ModelArrays* objectInfo;//FIXME: CHANGE THE NAME INTO SOMETHING MORE ADEQUATE
        Texture* texture;

    public:
        Model(ModelArrays* info=NULL, Texture* text=NULL);
        ~Model();
};

#endif // MODEL_H
