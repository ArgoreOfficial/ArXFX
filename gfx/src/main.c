#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gfx/gfx.h>
#include <gfx/impl/gfx_opengl.h>

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
		printf( "failed to create window\n" );
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
	glfwSwapInterval( 1 );
	
	gfxLoadOpenGL( glfwGetProcAddress );
	gfxViewport( 0, 0, 640, 480 );

	GfxGPUBufferDesc vbDesc;
	vbDesc.name = "vb";
	vbDesc.size = 64;
	vbDesc.type = GFX_BUFFER_TYPE_VERTEX;
	vbDesc.usage = GFX_BUFFER_USAGE_DYNAMIC_DRAW;

	GfxGPUBufferID vb = gfxCreateGPUBuffer( 0, &vbDesc );

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