#ifndef MODEL_H
#define MODEL_H

class Model
{
    //FIXME: ASSUME THAT IN "~Object()" WE DO "free(objectInfo)" and "free(texture)"
    private:
        ModelArrays* objectInfo;//FIXME: CHANGE THE NAME INTO SOMETHING MORE ADEQUATE
        Texture* texture;

    public:
        Model();
        Model(ModelArrays* info, Texture* text);
        ~Model();
};

#endif // MODEL_H
