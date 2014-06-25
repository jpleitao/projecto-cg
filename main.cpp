// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "Renderer.h"
#include "Player.h"
#include "GameWindow.h"
#include "ModelManager.h"
#include "World.h"
#include "Light.h"
#include "ObjectManager.h"
#include "Line.h"

int main (void) {
    GameWindow gameWindow;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Dark blue background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    // Enable depth test / Accept fragment if it closer to the camera than the former one
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glLineWidth(2);

    Renderer renderer;

    ModelManager modelManager;

    std::vector<Object*> objects;

    Player player(&renderer);

    ObjectManager objectManager(&renderer);
    objectManager.setLaserOrigin(vec2(0,-17.8));
    objectManager.setLaserDirection(vec2(0,1));

    World world(&modelManager ,&objectManager, "data/models/world");

    Object* test3 = new Object(new Line(vec3(0,LASER_Y+100,-25),vec3(0,LASER_Y+100,25)));
    //Object* test4 = new Object(new Line(vec3(0,LASER_Y+100,-25),vec3(0,LASER_Y+100,25)));
    //objectManager.addObject(test1);
    //objectManager.addObject(test2);
    objectManager.addObject(test3);
   // objectManager.addObject(test4);



    int frameNo = 0;

    Light blueLight(vec3(0,0,0), vec3(0,0,0));
    renderer.addLight(&blueLight);
    #define RED_LIGHT vec3(0.5,0,0)
    Light redLightFromAbove(vec3(0,2,0), RED_LIGHT);
    renderer.addLight(&redLightFromAbove);

    Light changingLight(vec3(0,0,0), vec3(0,0.6,0));
    renderer.addLight(&changingLight);

    Light changingLight2(vec3(0,0,0), vec3(0.2,0,0.5));
    renderer.addLight(&changingLight2);

    //Light topRedLight(vec3(0,2,19.19), vec3(1,0,0));
    //test2->setLaserLight(&topRedLight);
    //renderer.addLight(&topRedLight);
    
    float fact = 0.01;
    int frameCountDown = 0;
    while( gameWindow.shouldStayOpen() ) {
        gameWindow.beginFrame();

        objectManager.stopObjects();
        if ( frameCountDown ) frameCountDown--;
        //For debug on the collisions11
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_F ) == GLFW_PRESS){
            if ( frameCountDown == 0) {
                frameCountDown = 30;
                if ( blueLight.getIntensities().x == 0.0 )
                    blueLight.setIntensities(vec3(0.5,0.5,0.5));
                else
                    blueLight.setIntensities(vec3(0.0,0.0,0.0));
            }
        }
        if(glfwGetKey( gameWindow.getWindow(), GLFW_KEY_P ) == GLFW_PRESS) {
            objectManager.newTargetPosition();
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_R ) == GLFW_PRESS){
            objectManager.updateObjInFrontOfPlayer(&player);
            if ( objectManager.getObjInFrontOfPlayer() )
               objectManager.getObjInFrontOfPlayer() ->rotate(-1, vec3(0.0f, 1, 0.0f));
        }
        else if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_T ) == GLFW_PRESS){
            objectManager.updateObjInFrontOfPlayer(&player);
         if ( objectManager.getObjInFrontOfPlayer() )
               objectManager.getObjInFrontOfPlayer() ->rotate(1, vec3(0.0f, 1, 0.0f));
        }

        //printf("Frame %d\n", frameNo);
        

        /*
        for (int i = 0 ; i < lines.size(); i++) {
            std::vector<vec2> line = lines.at(i);
            printf("LINE %d ", i);
            for (int j = 0; j < line.size(); j++) {
                printf("(%f,%f)->", line.at(j).x, line.at(j).y);
            }
            printf("\n");
        }*/

        objectManager.moveObjects();
        objectManager.checkLimits();
        objectManager.collideAndFall();

        blueLight.setPosition(player.getPosition());
        changingLight.setPosition( vec3(glm::rotate(mat4(1.0f), (float)frameNo, vec3(0.0f,1.0f,0.0f))*vec4(vec3(3,4,3), 1.0f)));
        changingLight2.setPosition( vec3(glm::rotate(mat4(1.0f), (float)-frameNo, vec3(0.0f,1.0f,0.0f))*vec4(vec3(3,4,3), 1.0f)));

        vec3 intensity = changingLight2.getIntensities();

        if ( intensity[2] <= 0.2 && fact < 0) fact*=-1;
        else if ( intensity[2] >= 0.7  && fact > 0) fact*=-1;
        
        changingLight2.setIntensities(intensity+fact*vec3(0,1,1));
        //changingLight.setIntensities(vec3())
        
        if ( (frameNo % 1000) == 0)
            redLightFromAbove.setIntensities(0.0f*RED_LIGHT);
        else if ( (frameNo % 1005) == 0 )
            redLightFromAbove.setIntensities(RED_LIGHT);
        else if ((frameNo % 1010) == 0 )
            redLightFromAbove.setIntensities(0.0f*RED_LIGHT);
        else if ((frameNo % 1015) == 0 )
            redLightFromAbove.setIntensities(RED_LIGHT);
        else if ((frameNo % 1020) == 0 )
            redLightFromAbove.setIntensities(0.25f*RED_LIGHT);
        else if ((frameNo % 1025) == 0 )
            redLightFromAbove.setIntensities(0.5f*RED_LIGHT);
        else if ((frameNo % 1030) == 0 )
            redLightFromAbove.setIntensities(0.75f*RED_LIGHT);
        else if ((frameNo % 1035) == 0 )
            redLightFromAbove.setIntensities(RED_LIGHT);

        if ( frameNo++ > 0 ) {
            //printf("Updating: %f, %f\n", gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
            player.updateAngles(gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
            player.updatePosition(gameWindow.getStrafeOffset(), gameWindow.getFrontMoveOffset());

            //Check if the player is under the floor
            vec3 player_position = player.getPosition();

            //Check if the player is inside the field. If not, put him there!
            if (player_position[0] < MIN_X + PLAYER_OFFSET)
                player_position[0] = MIN_X + PLAYER_OFFSET;

            else if (player_position[0] > MAX_X - PLAYER_OFFSET)
                player_position[0] = MAX_X - PLAYER_OFFSET;

            if (player_position[2] < MIN_Z + PLAYER_OFFSET)
                player_position[2] = MIN_Z + PLAYER_OFFSET;

            else if (player_position[2] > MAX_Z - PLAYER_OFFSET)
                player_position[2] = MAX_Z - PLAYER_OFFSET;

            player_position[1] = OBSERVER_HEIGHT;//Has to be done

            //Reset the player's position
            player.updatePosition(player_position);
        }

        objectManager.processPlayer(&player);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objectManager.processLaser();
        objectManager.renderObjects();
        objectManager.clearLaser();

        gameWindow.endFrame();
    }

    return 0;
}
