#include "Texture.h"
#include "Renderer.h"
#include "Model.h"

Texture::Texture(const char* filename) {
    if ( filename == NULL ) {
        filename = "data/models/textures/dummy.bmp";
        printf("Loading new texture!\n");
    }
    this->textureId= -1;
    this->depthRenderBuffer = -1;
    this->frameBuffer = -1;
    loadTexture(filename);
}


//Loads the texture stored in "filename". The loaded texture ID is stored in the attribute "textureId"
void Texture::loadTexture(const char* filename)
{    
    loadImage(filename);

    if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
        printf("Your GPU does not provide framebuffer objects. Use a texture instead.");
        assert(0);
    }
/*
    // Set our rendered texture as our colour attachement #0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureId, 0);

    // Set the list of buffers to draw
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);*/
}

void Texture::genAndBindBuffers()
{
    /*
    glGenTextures(1, &this->textureId);
     
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, this->textureId);
     
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    */
}

void Texture::beginRender(Renderer* renderer, Model* destModel) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i( renderer->getTextureSamplerHandle(), 0);

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(renderer->getVertexUVHandle());
    glBindBuffer(GL_ARRAY_BUFFER, destModel->getObjectInfo()->getTexelsHandle());
    glVertexAttribPointer(
        renderer->getVertexUVHandle(),                   // The attribute we want to configure
        2,                            // size : U+V => 2
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void*)0                      // array buffer offset
    );
}

void Texture::finishRender(Renderer* renderer, Model* destModel) {
    glDisableVertexAttribArray(renderer->getVertexUVHandle());
}


void Texture::loadImage(const char* filename)
{


    this->imag.LoadBmpFile(filename);


    glGenTextures(1, &this->textureId);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        imag.GetNumCols(),
        imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());


    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);        
    //FIXME: Confirm that we want GL_LINEAR and GL_CLAMP in here!!!
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

}
