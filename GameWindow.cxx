#include "GameWindow.h"
#include <cstdio>
#include <cstdlib>


GameWindow::GameWindow(int width, int height, const char* title) :
            width(width), height(height) {

    // Initialise GLFW
    if( !glfwInit() )
    {
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

    lastFrameTime = glfwGetTime();
}

GameWindow::~GameWindow() {
    glfwTerminate();
}

bool GameWindow::shouldStayOpen() {
    return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0;
}

void GameWindow::beginFrame(){
    // Compute time difference between current and last frame
    currFrameTime = glfwGetTime();

    float deltaTime = float(currFrameTime - lastFrameTime);

    // Get mouse position
    double dx, dy;
    glfwGetCursorPos(window, &dx, &dy);


    screenMouseXOffset = width/2 - dx;
    screenMouseYOffset = height/2 - dy;

    printf("dx: %f, dy: %f, pDx: %f, pDy: %f\n", dx, dy, screenMouseXOffset, screenMouseYOffset);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, width/2, height/2);
}

void GameWindow::endFrame() {
    glfwPollEvents();
    swapBuffers();

    lastFrameTime = currFrameTime;
}

void GameWindow::swapBuffers() {
    return glfwSwapBuffers(window);
}
