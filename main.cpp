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

    /*Object* obj = new Object(new Model(), new Texture());
    Object* obj2 = new Object(new Model(), new Texture());
    Object* obj3 = new Object(new Model(), new Texture());
    Object* obj4 = new Object(new Model(), new Texture());*/
    //objects.push_back(obj2); objects.push_back(obj); objects.push_back(obj3);  objects.push_back(obj4);

    ObjectManager objectManager(&renderer);
    objectManager.setLaserOrigin(vec2(0,-25));
    objectManager.setLaserDirection(vec2(0,1));

    World world(&modelManager ,&objectManager, "data/models/world");

    

    std::vector<glm::vec4> vert;
    GLfloat cube_size = 2;

    vert.push_back(glm::vec4(cube_size/2,-cube_size/2,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,-cube_size/2,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,-cube_size/2,cube_size/2,1));
    vert.push_back(glm::vec4(cube_size/2,-cube_size/2,cube_size/2,1));
    Object* test1 = new Object(new Model(ObjLoader("data/models/obj/dummy.obj").load()), new Texture(), true, cube_size, cube_size, cube_size, vert);
    Object* test5 = new Object(new Model(ObjLoader("data/models/obj/dummy.obj").load()), new Texture(), true, cube_size, cube_size, cube_size, vert);
    Object* test2 = new Object(new Model(ObjLoader("data/models/obj/dummy.obj").load()), new Texture(), true, cube_size, cube_size, cube_size, vert);
    Object* test3 = new Object(new Line(vec3(0,LASER_Y+100,-25),vec3(0,LASER_Y+100,25)));
    //Object* test4 = new Object(new Line(vec3(0,LASER_Y+100,-25),vec3(0,LASER_Y+100,25)));
    objectManager.addObject(test1);
    objectManager.addObject(test2);
    objectManager.addObject(test3);
   // objectManager.addObject(test4);

    /*
    obj->rotate(33,vec3(0,1,0));
    obj->translate(vec3(0,2,0));
    obj2->translate(vec3(3.0f,0.0f,0.0f));
    obj4->translate(vec3(6.0f,0.0f,0.0f));
    */

    //test1->printStuff();
    test1->translate(vec3(0.0f,3.0f,-5.0f));
    
    test5->translate(vec3(0.0f,5.0f,-5.0f));
    //test1->printStuff();
    test1->scale(vec3(0.25f,0.25f,0.25f));
    //test1->printStuff();

    test2->translate(vec3(0.0f,1.0f,-5.0f));
    test2->rotate(41,vec3(0,1,0));
    //test3->translate(vec3(0.0f,1.0f,-5.0f));

    int frameNo = 0;

    Light blueLight(vec3(0,0,0), vec3(1,1,1));
    renderer.addLight(&blueLight);
    Light redLightFromAbove(vec3(0,2,0), vec3(1,0,0));
    renderer.addLight(&redLightFromAbove);

    Light changingLight(vec3(0,0,0), vec3(0,1,0));
    renderer.addLight(&changingLight);

    Light changingLight2(vec3(0,0,0), vec3(0,1,0));
    renderer.addLight(&changingLight2);

    //Light topRedLight(vec3(0,2,19.19), vec3(1,0,0));
    //test2->setLaserLight(&topRedLight);
    //renderer.addLight(&topRedLight);
    while( gameWindow.shouldStayOpen() ) {
        gameWindow.beginFrame();
        /*obj->rotate(1,vec3(0,1,0));*/

        objectManager.stopObjects();

        //FIXME: REFACTOR
        //For debug on the collisions only! - Remove this
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_L ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, 0.0f, 0.1f));
            test1->move(true,0.0f,0.1f);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_K ) == GLFW_PRESS){
            test1->translate(vec3(-0.1f, 0.0f, 0.0f));
            test1->move(true,-0.1f,0.0f);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_J ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, 0.0f, -0.1f));
            test1->move(true,0.0f,-0.1f);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_I ) == GLFW_PRESS){
            test1->translate(vec3(0.1f, 0.0f, 0.0f));
            test1->move(true,0.1f,0.0f);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_M ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, -0.1f, 0.0f));
            test1->move(true);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_N ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, 0.5f, 0.0f));
            test1->move(true);
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_R ) == GLFW_PRESS){
            test1->rotate(-1, vec3(0.0f, 1, 0.0f));
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_T ) == GLFW_PRESS){
            test1->rotate(1, vec3(0.0f, 1, 0.0f));
        }

        //printf("Frame %d\n", frameNo);
        std::vector<std::vector<vec2> > lines = test1->getBoundingBoxLines();

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
        changingLight2.setIntensities(vec3((float)(frameNo/10 % 256) / 512.0, 0.0f,((float)((frameNo/10 + 128) % 256)) / 512.0));
        //changingLight.setIntensities(vec3())


    //test2->rotate(0.5,vec3(0,1,0));
        

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

            //Reset the player's position
            player.setPosition(vec3(player_position[0], OBSERVER_HEIGHT, player_position[2]));
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objectManager.processLaser();
        objectManager.renderObjects();
        objectManager.clearLaser();

        gameWindow.endFrame();
    }

    return 0;
}
