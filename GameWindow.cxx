#include "GameWindow.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>


GameWindow::GameWindow(int width, int height, const char* title) :
            width(width), height(height) {

    // Initialise GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit(0);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    if ( !(window = glfwCreateWindow( width, height, title, NULL, NULL)) ) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);

    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, width/2, height/2);
    glfwSetTime( 0.0 );
    lastFrameTime = glfwGetTime();
    this->screenMouseXOffset = this->screenMouseYOffset = this->keyPressOffsetW = this->keyPressOffsetA = this->keyPressOffsetS = this->keyPressOffsetD = 0;

}

GameWindow::~GameWindow() {
    glfwTerminate();
}

bool GameWindow::shouldStayOpen() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0;
}

void GameWindow::handleMouse() {
    // Get mouse position
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);


    if ( ! (fabs(dx) <= 0.1 || fabs(dy) <= 0.1) ) {
        screenMouseXOffset = width/2.0 - dx;
        screenMouseYOffset = height/2.0 - dy;
    }



    //printf("dx: %f, dy: %f, pDx: %f, pDy: %f\n", dx, dy, screenMouseXOffset, screenMouseYOffset);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, width/2, height/2);
}

void GameWindow::handleWASD() {
    float deltaTime = float(currFrameTime - lastFrameTime);
    // Move forward
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS)
        keyPressOffsetW =  deltaTime;
    else
        keyPressOffsetW = 0;

    // Move backward
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS)
        keyPressOffsetS =  deltaTime;
    else
        keyPressOffsetS = 0;

    // Strafe right
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS)
        keyPressOffsetD =  deltaTime;
    else
        keyPressOffsetD = 0;

    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS)
        keyPressOffsetA =  deltaTime;
    else
        keyPressOffsetA = 0;
}

void GameWindow::beginFrame(){
    // Compute time difference between current and last frame
    currFrameTime = glfwGetTime();

    handleMouse();
    handleWASD();
}

void GameWindow::endFrame() {
    glfwPollEvents();
    swapBuffers();

    lastFrameTime = currFrameTime;
}

void GameWindow::swapBuffers() {
    return glfwSwapBuffers(window);
}
