// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
GLFWwindow* window;

#include "Renderer.h"

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Create and compile our GLSL program from the shaders
	Renderer renderer;

	std::vector<Object*> objects;
	
	Object* obj = new Object(new Model(), new Texture());
	Object* obj2 = new Object(new Model(), new Texture());
	Object* obj3 = new Object(new Model(), new Texture());
	Object* obj4 = new Object(new Model(), new Texture());
	//new Texture();
	objects.push_back(obj2); objects.push_back(obj); objects.push_back(obj3);  objects.push_back(obj4);
	//obj->scale(vec3(0.25f,0.20f,0.20f));
	obj->rotate(33,vec3(0,1,0));
	obj2->translate(vec3(3.0f,0.0f,0.0f));
	obj4->translate(vec3(-3.0f,0.0f,0.0f));

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.render(objects);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();


	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

