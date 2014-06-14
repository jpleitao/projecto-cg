#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "common.h"

class GameWindow
{
    GLFWwindow* window;
    unsigned int width, height;

    double lastFrameTime,currFrameTime;

    double screenMouseXOffset, screenMouseYOffset;

    private:
        void swapBuffers();

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
};

#endif // GAMEWINDOW_H
