#include <stdio.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glad/glad.h>

#include <math.h>

#include <afx/Renderer/LowLevel/LowLevelGraphics.h>

GLFWwindow* window;

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
	
	afx::ILowLevelGraphics* g_graphics = afx::ILowLevelGraphics::Registry::createFromName( "OpenGL" );
	g_graphics->init();
	g_graphics->viewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

	uint32_t frameNumber = 0;

	while ( !glfwWindowShouldClose( window ) )
	{
		// update screen data buffer
		int width, height;
		glfwGetWindowSize( window, &width, &height );

		g_graphics->viewport( 0, 0, width, height );
		
		float flash = fabs( sin( frameNumber / 60.0f ) );
		g_graphics->setClearColor( flash, 0.0f, flash, 1.0f );
		g_graphics->clearRenderTarget( (afx::ClearMask)( afx::ClearMask::kCOLOR | afx::ClearMask::kDEPTH ) );

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
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "ArX FX", NULL, NULL );

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
