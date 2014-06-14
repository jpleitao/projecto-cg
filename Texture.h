#ifndef TEXTURE_H
#define TEXTURE_H

#include <assert.h>
#include "common.h"
#include "RgbImage.h"

class Model;
class Renderer;

class Texture{

    private:
       GLuint textureId;
       GLuint depthRenderBuffer;
       GLuint frameBuffer;
       RgbImage imag;

       void loadImage(const char* filename);
       void genAndBindBuffers();
       void loadTexture(const char* filename);
      public:
       Texture(const char* filename = NULL);
       void beginRender(Renderer* renderer, Model* destModel);
       void finishRender(Renderer* renderer, Model* destModel);
       GLuint getTextureId() { return textureId; }
};


#endif // TEXTURE_H
