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

int main (void) {	
	GameWindow gameWindow;
	
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test / Accept fragment if it closer to the camera than the former one
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	Renderer renderer;

    ModelManager modelManager;
	
	std::vector<Object*> objects;	

	Player player(&renderer);

    /*Object* obj = new Object(new Model(), new Texture());
	Object* obj2 = new Object(new Model(), new Texture());
	Object* obj3 = new Object(new Model(), new Texture());
    Object* obj4 = new Object(new Model(), new Texture());*/
    //objects.push_back(obj2); objects.push_back(obj); objects.push_back(obj3);  objects.push_back(obj4);

    World world(&modelManager ,&renderer, "data/models/world");

    ObjectManager objectManager(&renderer);

    std::vector<glm::vec4> vert;
    GLfloat cube_size = 2;

    vert.push_back(glm::vec4(cube_size/2,cube_size,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,cube_size,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,cube_size,cube_size/2,1));
    vert.push_back(glm::vec4(cube_size/2,cube_size,cube_size/2,1));
    Object* test1 = new Object(new Model(), new Texture(), true, cube_size, cube_size, cube_size, vert);
    Object* test2 = new Object(new Model(), new Texture(), true, cube_size, cube_size, cube_size, vert);
    objectManager.addObject(test1);
    objectManager.addObject(test2);
	
    /*
	obj->rotate(33,vec3(0,1,0));
	obj->translate(vec3(0,2,0));
	obj2->translate(vec3(3.0f,0.0f,0.0f));
    obj4->translate(vec3(6.0f,0.0f,0.0f));
    */

    //test1->printStuff();
    test1->translate(vec3(0.0f,3.0f,-5.0f));
    //test1->printStuff();
    test1->scale(vec3(0.25f,0.25f,0.25f));
    //test1->printStuff();

    test2->translate(vec3(0.0f,1.0f,-5.0f));

	int frameNo = 0;

    Light blueLight(vec3(0,0,0), vec3(1,1,1));
    renderer.addLight(&blueLight);
    Light redLightFromAbove(vec3(0,2,0), vec3(1,0,0));
    renderer.addLight(&redLightFromAbove);

    Light changingLight(vec3(0,0,0), vec3(0,1,0));
    renderer.addLight(&changingLight);

    Light changingLight2(vec3(0,0,0), vec3(0,1,0));
    renderer.addLight(&changingLight2);
	while( gameWindow.shouldStayOpen() ) {
		gameWindow.beginFrame();
        /*obj->rotate(1,vec3(0,1,0));*/

        //For debug on the collisions only! - Remove this
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_L ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, 0.0f, 0.1f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_K ) == GLFW_PRESS)
            test1->translate(vec3(-0.1f, 0.0f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_J ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, 0.0f, -0.1f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_I ) == GLFW_PRESS)
            test1->translate(vec3(0.1f, 0.0f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_M ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, -0.1f, 0.0f));
            if (test1->getCenterY() < (test1->getHeight()/2) )
                test1->translate(vec3(0.0f, 0.1f , 0.0f));
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_N ) == GLFW_PRESS){
            test1->translate(vec3(0.0f, 0.5f, 0.0f));
            //FIXME: Verify the height, like in the previous one, but in the other direction
        }
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_R ) == GLFW_PRESS)
            test1->rotate(1, vec3(0.0f, 1, 0.0f));

        blueLight.setPosition(player.getPosition());       
        changingLight.setPosition( vec3(glm::rotate(mat4(1.0f), (float)frameNo, vec3(0.0f,1.0f,0.0f))*vec4(vec3(3,4,3), 1.0f))); 
        changingLight2.setPosition( vec3(glm::rotate(mat4(1.0f), (float)-frameNo, vec3(0.0f,1.0f,0.0f))*vec4(vec3(3,4,3), 1.0f))); 
        changingLight2.setIntensities(vec3((float)(frameNo/10 % 256) / 512.0, 0.0f,((float)((frameNo/10 + 128) % 256)) / 512.0));
        //changingLight.setIntensities(vec3())

        objectManager.collideAndFall();        


		if ( frameNo++ > 0 ) {
            //printf("Updating: %f, %f\n", gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updateAngles(gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updatePosition(gameWindow.getStrafeOffset(), gameWindow.getFrontMoveOffset());

            //Check if the player is under the floor
            vec3 player_position = player.getPosition();

            //Check if the player is inside the field. If not, put him there!
            if (player_position[0] < MIN_X)
                player_position[0] = MIN_X;
            
            else if (player_position[0] > MAX_X)
                player_position[0] = MAX_X;

            if (player_position[2] < MIN_Z)
                player_position[2] = MIN_Z;

            else if (player_position[2] > MAX_Z)
                player_position[2] = MAX_Z;

            //Reset the player's height
            player.setPosition(vec3(player_position[0], OBSERVER_HEIGHT, player_position[2]));
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        objectManager.renderObjects();        
        world.render();

		gameWindow.endFrame();
    }

	return 0;
}

