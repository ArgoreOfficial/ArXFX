#include <stdio.h>

#include <ARG/gfx.h>
#include <ARG/gfh/mesh.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glad/glad.h>

#include <math.h>

GLFWwindow* window;
ArgGfxContext gpuCtx;

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

// function definitions ///////////////////////////////////////////////////////////////

int initWindow();
void deinitWindow();

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	if ( !initWindow() ) return 1;

	glfwSwapInterval( 1 );
	
	argGfxInit();
	argGfxCreateContext( &gpuCtx );

	argGfxViewport( gpuCtx, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

	uint32_t frameNumber = 0;

	while ( !glfwWindowShouldClose( window ) )
	{
		// update screen data buffer
		int width, height;
		glfwGetWindowSize( window, &width, &height );
		argGfxViewport( gpuCtx, 0, 0, width, height );
		
		float flash = fabs( sin( frameNumber / 60.0f ) );
		argGfxSetClearColor( gpuCtx, flash, 0.0f, flash, 1.0f );
		argGfxClearRenderTarget( gpuCtx, (ArgGfxClearMask)( ARG_GFX_CLEAR_MASK_COLOR | ARG_GFX_CLEAR_MASK_DEPTH ) );

		glfwSwapBuffers( window );
		glfwPollEvents();

		frameNumber++;
	}

	deinitWindow();

	return 0;
}

// impl ///////////////////////////////////////////////////////////////////////////////

int initWindow()
{
	if( !glfwInit() )
		return 0;

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, 1 );
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "argGfx", NULL, NULL );

	glfwMakeContextCurrent( window );

	if( !window )
	{
		glfwTerminate();
		printf( "failed to create window\n" );
		return 0;
	}

	HWND hWnd = glfwGetWin32Window( window );
	SetWindowDisplayAffinity( hWnd, WDA_NONE );

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////

void deinitWindow()
{
	glfwDestroyWindow( window );
	glfwTerminate();
}
