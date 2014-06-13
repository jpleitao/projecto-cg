#include "Texture.h"

Texture::Texture(){
    //FIXME
    this->imag = RgbImage::RgbImage();
    this->textureId= -1;
    this->depthRenderBuffer = -1;
    this->frameBuffer = -1;
}


//Loads the texture stored in "filename". The loaded texture ID is stored in the attribute "textureId"
void Texture::loadTexture(const char* filename)
{
    genAndBindBuffers();

    loadImage(filename);

    if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
        printf("Your GPU does not provide framebuffer objects. Use a texture instead.");
        assert(0);
    }

    // Set our rendered texture as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureId, 0);

    // Set the list of buffers to draw
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        assert(0);
}

void Texture::genAndBindBuffers()
{
    //Buffer with our texture
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    //Frame Buffer
    glGenFramebuffers(1, &this->frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);

    //Deth Buffer
    glGenRenderbuffers(1, &this->depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthRenderBuffer);
}

void Texture::loadImage(const char* filename)
{
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //FIXME: Confirm that we want GL_LINEAR and GL_CLAMP in here!!!
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

//Renders the texture. FIXME: WHEN DO WE CALL THIS AND HOW DO WE DETERMINE TO WHAT OBJECTS MUST WE APPLY THE TEXTURE?
void Texture::renderTexture()
{
    //Render the texture to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport(0,0,1024,768);//FIXME: 1024 and 768 are hard-coded values -- CHANGE THIS!

    //Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 /* CODE FOR RENDERING THE TEXTURE FROM THE TUTORIAL
  * NOTE THAT THEY USE A SHADER FOR THAT (see Tutorial 14 WobblyTexture.fragmentshader)

    //Use our shader
    glUseProgram(quad_programID);

    //Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    //Set our "renderedTexture" sampler to user Texture Unit 0
    glUniform1i(texID, 0);
*/
}
