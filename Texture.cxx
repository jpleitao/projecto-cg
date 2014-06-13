#include "Texture.h"

Texture::Texture(){
    //FIXME
    this->id = -1;
    this->imag = new RgbImage();
    this->text = -1;
}

void Texture::loadTexture(const char* filename)
{
    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    /*FIXME: Confirm that we want GL_LINEAR and GL_CLAMP in here!!!*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    this->imag.LoadBmpFile(filename);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, this>imag.GetNumCols(), this->imag.GetNumRows(), 0,
                 GL_RGB, GL_UNSIGNED_BYTE, this->imag.ImageData());
}
