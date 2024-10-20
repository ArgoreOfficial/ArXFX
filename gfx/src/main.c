#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "gfx/gfx.h"

GLFWwindow* window;

int initWindow()
{
	if ( !glfwInit() )
		return 0;


	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	window = glfwCreateWindow( 640, 480, "gfx", NULL, NULL );

	if ( !window )
	{
		glfwTerminate();
		return 0;
	}

	return 1;
}

void deinitWindow()
{
	glfwDestroyWindow( window );
	glfwTerminate();
}

int main()
{
	if ( !initWindow() )
		return 1;

	glfwMakeContextCurrent( window );
	
	gfxLoadOpenGL( glfwGetProcAddress );

	glfwSwapInterval( 1 );

	gfxViewport( 0, 0, 640, 480 );

	while ( !glfwWindowShouldClose( window ) )
	{
		gfxSetClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
		gfxClearRenderTarget( GFX_CLEAR_MASK_COLOR );

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	deinitWindow();

	return 0;
}