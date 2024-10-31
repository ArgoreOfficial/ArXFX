#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define TST
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
#define NUM_ATTRIBS 2
ArgGfxVertexLayout vertexLayout;
ArgGfxVertexAttrib vertexAttribs[ NUM_ATTRIBS ];
unsigned int emptyVAO;

ArgGfxBuffer vb, ib;
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

	// remove
	glCreateVertexArrays( 1, &emptyVAO );

	createShaders();
	initBuffers();

	argGfxBindPipeline( pipeline );
	argGfxBindBuffer( vb );
	argGfxBindBuffer( ib );

	argGfxBindBufferIndex( screenDataBuffer, 0 );

	while ( !glfwWindowShouldClose( window ) )
	{
		glfwGetWindowSize( window, &screenData.width, &screenData.height );
		argGfxViewport( 0, 0, screenData.width, screenData.height );
		argGfxBufferSubData( screenDataBuffer, &screenData, sizeof( ScreenData ), 0 );

		argGfxSetClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		argGfxClearRenderTarget( ARG_GFX_CLEAR_MASK_COLOR );

		argGfxDrawIndexed( 6 );

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
	window = glfwCreateWindow( 640, 480, "argGfx", NULL, NULL );

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
	FILE* vsFile = fopen( "vs2.glsl", "r" );
	FILE* fsFile = fopen( "fs2.glsl", "r" );

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


	// we're using a stack allocated vertex layout here, but it could just as well be heap allocated
	ArgGfxVertexAttrib posAttrib = { "POSITION", 3, ARG_FLOAT, false, sizeof(float) * 3 };
	ArgGfxVertexAttrib colAttrib = { "COLOR",    3, ARG_FLOAT, false, sizeof(float) * 3 };
	vertexAttribs[ 0 ] = posAttrib;
	vertexAttribs[ 1 ] = colAttrib;

	vertexLayout.attributes = vertexAttribs;
	vertexLayout.numAttributes = NUM_ATTRIBS;
	vertexLayout.stride = sizeof( Vertex );

	ArgGfxPipelineDesc pipelineDesc;
	pipelineDesc.fragmentProgram = fs;
	pipelineDesc.vertexProgram = vs;
	pipelineDesc.pVertexLayout = &vertexLayout;
	pipeline = argGfxCreatePipeline( 0, &pipelineDesc );
		
}

///////////////////////////////////////////////////////////////////////////////////////

void initBuffers()
{
	// create vertex buffer
	Vertex vertices[] = {
		{ -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f },
		{ -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f },
		{  0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f }
	};

	ArgGfxBufferDesc vbDesc;
	vbDesc.type  = ARG_GFX_BUFFER_TYPE_VERTEX;
	vbDesc.usage = ARG_GFX_BUFFER_USAGE_STATIC_DRAW;
	vbDesc.size  = sizeof( vertices );

	vb = argGfxCreateBuffer( 0, &vbDesc );
	argGfxBufferSubData( vb, vertices, sizeof( vertices ), 0 );

	// create index buffer
	unsigned int indices[] = { 0, 1, 2, 1, 3, 2 };
	
	ArgGfxBufferDesc ibDesc;
	ibDesc.type  = ARG_GFX_BUFFER_TYPE_INDEX;
	ibDesc.usage = ARG_GFX_BUFFER_USAGE_STATIC_DRAW;
	ibDesc.size  = sizeof( indices );
	
	ib = argGfxCreateBuffer( 0, &ibDesc );
	argGfxBufferSubData( ib, indices, sizeof( indices ), 0 );
	
	// create screen data buffer
	ArgGfxBufferDesc screenDataDesc;
	screenDataDesc.size = sizeof( ScreenData );
	screenDataDesc.type = ARG_GFX_BUFFER_TYPE_DYNAMIC;
	screenDataDesc.usage = ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW;

	screenDataBuffer = argGfxCreateBuffer( 0, &screenDataDesc );

}