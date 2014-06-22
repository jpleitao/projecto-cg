// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "Renderer.h"
#include "Player.h"
#include "GameWindow.h"
#include "ModelManager.h"
#include "World.h"

int main (void) {	
	GameWindow gameWindow;
	
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test / Accept fragment if it closer to the camera than the former one
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);

	Renderer renderer;

    ModelManager modelManager;
	
	std::vector<Object*> objects;	

	Player player(&renderer);

	Object* obj = new Object(new Model(), new Texture());
	Object* obj2 = new Object(new Model(), new Texture());
	Object* obj3 = new Object(new Model(), new Texture());
	Object* obj4 = new Object(new Model(), new Texture());
    //objects.push_back(obj2); objects.push_back(obj); objects.push_back(obj3);  objects.push_back(obj4);

    World* world = new World(&modelManager ,&renderer, "data/models/world");

    std::vector<glm::vec4> vert;
    GLfloat cube_size = 2;

    vert.push_back(glm::vec4(cube_size/2,cube_size,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,cube_size,-cube_size/2,1));
    vert.push_back(glm::vec4(-cube_size/2,cube_size,cube_size/2,1));
    vert.push_back(glm::vec4(cube_size/2,cube_size,cube_size/2,1));
    Object* test1 = new Object(new Model(), new Texture(), true, cube_size, cube_size, cube_size, vert);
    Object* test2 = new Object(new Model(), new Texture(), true, cube_size, cube_size, cube_size, vert);
    //objects.push_back(test1); objects.push_back(test2);
	
    /*
	obj->rotate(33,vec3(0,1,0));
	obj->translate(vec3(0,2,0));
	obj2->translate(vec3(3.0f,0.0f,0.0f));
    obj4->translate(vec3(6.0f,0.0f,0.0f));
    */

    //test2->translate(vec3(0.0f,3.0f,0.0f));
    test2->rotate(30,vec3(0,1,0));
    test1->translate(vec3(0.0f,0.0f,-5.0f));

	int frameNo = 0;
	while( gameWindow.shouldStayOpen() ) {
		gameWindow.beginFrame();
		obj->rotate(1,vec3(0,1,0));

        //For debug on the collisions only! - Remove this
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_L ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, 0.0f, 0.1f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_K ) == GLFW_PRESS)
            test1->translate(vec3(-0.1f, 0.0f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_J ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, 0.0f, -0.1f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_I ) == GLFW_PRESS)
            test1->translate(vec3(0.1f, 0.0f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_M ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, -0.1f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_N ) == GLFW_PRESS)
            test1->translate(vec3(0.0f, 0.1f, 0.0f));
        if (glfwGetKey( gameWindow.getWindow(), GLFW_KEY_R ) == GLFW_PRESS)
            test1->rotate(1, vec3(0.0f, 1, 0.0f));

        //Check for collisions! -- For each object test it with the ones after him
        for (int i=0;i<objects.size();i++){
            Object* current = objects[i];

            for (int j=i+1;j<objects.size();j++){
                if (current->collision(objects[j])){
                    std::cout << "COLLISION!\n";
                    //assert(0);
                }
            }
        }


		if ( frameNo++ > 0 ) {
            //printf("Updating: %f, %f\n", gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updateAngles(gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updatePosition(gameWindow.getStrafeOffset(), gameWindow.getFrontMoveOffset());
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render(objects);

		gameWindow.endFrame();
    }

	return 0;
}

