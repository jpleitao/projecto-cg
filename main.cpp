// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#include "Renderer.h"
#include "Player.h"
#include "GameWindow.h"

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
	
	std::vector<Object*> objects;	

	Player player(&renderer);

	Object* obj = new Object(new Model(), new Texture());
	Object* obj2 = new Object(new Model(), new Texture());
	Object* obj3 = new Object(new Model(), new Texture());
	Object* obj4 = new Object(new Model(), new Texture());
	objects.push_back(obj2); objects.push_back(obj); objects.push_back(obj3);  objects.push_back(obj4);
	

	obj->rotate(33,vec3(0,1,0));
	obj->translate(vec3(0,2,0));
	obj2->translate(vec3(3.0f,0.0f,0.0f));
	obj4->translate(vec3(6.0f,0.0f,0.0f));

	int frameNo = 0;
	while( gameWindow.shouldStayOpen() ) {
		gameWindow.beginFrame();
		obj->rotate(1,vec3(0,1,0));

		if ( frameNo++ > 0 ) {
			printf("Updating: %f, %f\n", gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updateAngles(gameWindow.getFrameScreenXOffset(), gameWindow.getFrameScreenYOffset());
			player.updatePosition(gameWindow.getStrafeOffset(), gameWindow.getFrontMoveOffset());
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.render(objects);

		gameWindow.endFrame();
	} 

	return 0;
}

