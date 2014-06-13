#ifndef TEXTURE_H
#define TEXTURE_H

#include <assert.h>
#include "common.h"
#include "RgbImage.h"

class Texture{

    private:
       GLuint textureId;
       GLuint depthRenderBuffer;
       GLuint frameBuffer;
       RgbImage imag;

       void loadImage(const char* filename);
       void genAndBindBuffers();

      public:
       Texture();
       void loadTexture(const char* filename);
       void renderTexture();

};


#endif // TEXTURE_H
