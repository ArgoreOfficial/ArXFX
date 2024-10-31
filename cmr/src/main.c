#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gfx/gfx.h>
#include <gfx/impl/gfx_opengl.h>

#include <glad/glad.h>

#include <malloc.h>
#include <memory.h>

// types //////////////////////////////////////////////////////////////////////////////

typedef struct Vertex
{
	float position[ 3 ];
	float color[ 3 ];
} Vertex;

typedef struct ScreenData
{
	int width;
	int height;
} ScreenData;

// variables //////////////////////////////////////////////////////////////////////////

GLFWwindow* window;
ArgGfxPipeline pipeline;
unsigned int emptyVAO;

ArgGfxBuffer vb;
ArgGfxBuffer screenDataBuffer;

ScreenData screenData;

// function definitions ///////////////////////////////////////////////////////////////

int initWindow();
void deinitWindow();

size_t getFileSize( FILE* _pFile );

void createShaders();
void initBuffers();

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	if ( !initWindow() )
		return 1;

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );
	
	argGfxLoadOpenGL( glfwGetProcAddress );
	argGfxViewport( 0, 0, 640, 480 );

	createShaders();
	initBuffers();

	argGfxBindPipeline( pipeline );
	argGfxBindBufferIndex( vb, 0 );
	argGfxBindBufferIndex( screenDataBuffer, 1 );
	
	while ( !glfwWindowShouldClose( window ) )
	{
		glfwGetWindowSize( window, &screenData.width, &screenData.height );
		argGfxViewport( 0, 0, screenData.width, screenData.height );
		argGfxBufferSubData( screenDataBuffer, &screenData, sizeof( ScreenData ), 0 );

		argGfxSetClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		argGfxClearRenderTarget( ARG_GFX_CLEAR_MASK_COLOR );

		// argGfxBeginDraw();
		argGfxDraw( 0, 3 );
		// argGfxEndDraw();

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	// not implemented
	argGfxDestroyBuffer( vb );
	argGfxDestroyBuffer( screenDataBuffer );
	argGfxDestroyPipeline( pipeline );

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
	window = glfwCreateWindow( 640, 480, "Chimera - gfx", NULL, NULL );

	if( !window )
	{
		glfwTerminate();
		printf( "failed to create window\n" );
		return 0;
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////

void deinitWindow()
{
	glfwDestroyWindow( window );
	glfwTerminate();
}

///////////////////////////////////////////////////////////////////////////////////////

size_t getFileSize( FILE* _pFile )
{
	fseek( _pFile, 0, SEEK_END );
	size_t fileSize = ftell( _pFile );
	rewind( _pFile );
	return fileSize;
}

///////////////////////////////////////////////////////////////////////////////////////

void createShaders()
{
	FILE* vsFile = fopen( "vs.glsl", "r" );
	FILE* fsFile = fopen( "fs.glsl", "r" );

	size_t vsSize = getFileSize( vsFile ) + 1;
	char* vsBuffer = malloc( vsSize );
	if( vsBuffer )
	{
		memset( vsBuffer, 0, vsSize );
		fread( vsBuffer, 1, vsSize, vsFile );
		vsBuffer[ vsSize - 1 ] = 0;
	}

	size_t fsSize = getFileSize( fsFile ) + 1;
	char* fsBuffer = malloc( fsSize );
	if( fsBuffer )
	{
		memset( fsBuffer, 0, fsSize );
		fread( fsBuffer, 1, fsSize, fsFile );
		fsBuffer[ fsSize - 1 ] = 0;
	}

	fclose( vsFile );
	fclose( fsFile );

	ArgGfxProgramDesc vsDesc;
	vsDesc.type = ARG_GFX_SHADER_TYPE_VERTEX;
	vsDesc.source = vsBuffer;

	ArgGfxProgramDesc fsDesc;
	fsDesc.type = ARG_GFX_SHADER_TYPE_FRAGMENT;
	fsDesc.source = fsBuffer;

	ArgGfxProgram vs = argGfxCreateProgram( 0, &vsDesc );
	ArgGfxProgram fs = argGfxCreateProgram( 0, &fsDesc );

	if( vsBuffer ) free( vsBuffer );
	if( fsBuffer ) free( fsBuffer );

	ArgGfxPipelineDesc pipelineDesc;
	pipelineDesc.fragmentProgram = fs;
	pipelineDesc.vertexProgram = vs;
	pipelineDesc.pVertexLayout = NULL;
	pipeline = argGfxCreatePipeline( 0, &pipelineDesc );
}

///////////////////////////////////////////////////////////////////////////////////////

void initBuffers()
{
	// remove
	glGenVertexArrays( 1, &emptyVAO );
	glBindVertexArray( emptyVAO );

	// create vertex buffer
	Vertex vertices[ 3 ] = {
		{ -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f },
		{  0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f },
		{  0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f }
	};

	ArgGfxBufferDesc vbDesc;
	vbDesc.size = sizeof( vertices );
	vbDesc.type = ARG_GFX_BUFFER_TYPE_DYNAMIC;
	vbDesc.usage = ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW;

	vb = argGfxCreateBuffer( 0, &vbDesc );
	argGfxBufferSubData( vb, vertices, sizeof( vertices ), 0 );

	// create screen data buffer
	ArgGfxBufferDesc screenDataDesc;
	screenDataDesc.size = sizeof( ScreenData );
	screenDataDesc.type = ARG_GFX_BUFFER_TYPE_DYNAMIC;
	screenDataDesc.usage = ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW;

	screenDataBuffer = argGfxCreateBuffer( 0, &screenDataDesc );
}