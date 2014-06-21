#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "common.h"

class GameWindow
{
    GLFWwindow* window;
    unsigned int width, height;

    double lastFrameTime,currFrameTime;

    double screenMouseXOffset, screenMouseYOffset;
    double keyPressOffsetW, keyPressOffsetA, keyPressOffsetS, keyPressOffsetD;

    private:
        void swapBuffers();
        void handleMouse();
        void handleWASD();

    public:
        GameWindow(int width=1024, int height=768, const char* title = "LaserRecoil" );
        ~GameWindow();

        bool shouldStayOpen();        

        void beginFrame();
        void endFrame();


        unsigned int getWidth()         { return this->width; }
        unsigned int getHeight()        { return this->height; }
        double getFrameScreenXOffset() { return this->screenMouseXOffset; }
        double getFrameScreenYOffset() { return this->screenMouseYOffset; }

        double getStrafeOffset() { return this->keyPressOffsetD-this->keyPressOffsetA; }
        double getFrontMoveOffset() { return this->keyPressOffsetW-this->keyPressOffsetS; }

        /*FIXME! This is just here for testing the collisions, this will later be removed!
         *This is just a hack, because I don't want to spend too much time dealing with the inputs for now
         */
        GLFWwindow* getWindow(){ return this->window;}
};

#endif // GAMEWINDOW_H
