#include "Texture.h"

Texture::Texture(){
    //FIXME
    this->imag = RgbImage::RgbImage();
    this->textureId= -1;
    this->depthRenderBuffer = -1;
}


/*Loads the texture stored in "filename". The loaded texture ID is stored in the attribute "textureId"*/
void Texture::loadTexture(const char* filename)
{
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    /*FIXME: Confirm that we want GL_LINEAR and GL_CLAMP in here!!!*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    this->imag.LoadBmpFile(filename);

    glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());
}

/*Renders the texture. FIXME: WHEN DO WE CALL THIS AND HOW DO WE DETERMINE TO WHAT OBJECTS MUST WE APPLY THE TEXTURE?*/
void Texture::renderTexture()
{
    if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
        printf("Your GPU does not provide framebuffer objects. Use a texture instead.");
        assert(0);
    }

    glGenRenderbuffers(1, &this->depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthRenderBuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureId, 0);

    // Set the list of buffers to draw
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        assert(0);
}
