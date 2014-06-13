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
       void loadTexture(const char* filename);
      public:
       Texture(const char* filename = NULL);
       GLuint getTextureId() { return textureId; }
       void renderTexture();

};


#endif // TEXTURE_H
