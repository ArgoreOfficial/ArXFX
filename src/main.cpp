#include <stdio.h>

#ifdef AFX_SUPPORT_GLFW
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif
#include <afx/Renderer/LowLevel/LowLevelGraphics.h>

#ifdef AFX_SUPPORT_GLFW
GLFWwindow* window;
#endif

const int WINDOW_WIDTH  = 640;
const int WINDOW_HEIGHT = 480;

// function definitions ///////////////////////////////////////////////////////////////

int initWindow();
void deinitWindow();

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	if ( !initWindow() ) return 1;
#ifdef AFX_SUPPORT_GLFW
	glfwSwapInterval( 1 );
#endif
	
	afx::ILowLevelGraphics* g_graphics = afx::ILowLevelGraphics::Registry::createFromName( "OpenGL" );
	g_graphics->init();
	g_graphics->viewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

	uint32_t frameNumber = 0;
#ifdef AFX_SUPPORT_GLFW
	while ( !glfwWindowShouldClose( window ) )
	{
		// update screen data buffer
		int width, height;
		glfwGetWindowSize( window, &width, &height );

		g_graphics->viewport( 0, 0, width, height );
		
		float flash = fabs( sin( frameNumber / 60.0f ) );
		g_graphics->clearColor( flash, 0.0f, flash, 1.0f );
		
		glfwSwapBuffers( window );
		glfwPollEvents();

		frameNumber++;
	}

	deinitWindow();
#endif

	return 0;
}

// impl ///////////////////////////////////////////////////////////////////////////////

int initWindow()
{
#ifdef AFX_SUPPORT_GLFW
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
#endif

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////

void deinitWindow()
{
#ifdef AFX_SUPPORT_GLFW
	glfwDestroyWindow( window );
	glfwTerminate();
#endif
}

