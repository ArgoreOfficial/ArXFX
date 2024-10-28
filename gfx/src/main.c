#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gfx/gfx.h>
#include <gfx/impl/gfx_opengl.h>
#include <glad/glad.h>

#include <malloc.h>
#include <memory.h>

static GLFWwindow* window;
static GfxPipeline pipeline;
static GfxGPUBuffer vb;
static unsigned int emptyVAO;

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

size_t getFileSize( FILE* _pFile )
{
	fseek( _pFile, 0, SEEK_END );
	size_t fileSize = ftell( _pFile );
	rewind( _pFile );
	return fileSize;
}

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

	GfxProgramDesc vsDesc;
	vsDesc.type = GFX_SHADER_TYPE_VERTEX;
	vsDesc.source = vsBuffer;
	
	GfxProgramDesc fsDesc;
	fsDesc.type = GFX_SHADER_TYPE_FRAGMENT;
	fsDesc.source = fsBuffer;

	GfxProgram vs = gfxCreateProgram( 0, &vsDesc );
	GfxProgram fs = gfxCreateProgram( 0, &fsDesc );

	if( vsBuffer ) free( vsBuffer );
	if( fsBuffer ) free( fsBuffer );

	GfxPipelineDesc pipelineDesc;
	pipelineDesc.fragmentProgram = fs;
	pipelineDesc.vertexProgram = vs;
	pipelineDesc.pVertexLayout = NULL;
	pipeline = gfxCreatePipeline( 0, &pipelineDesc );
}

typedef struct Vertex
{
	float position[ 3 ];
} Vertex;

void createVertexData()
{
	Vertex vertices[ 3 ] = {
		{ -0.5f, -0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{  0.0f,  0.5f, 0.0f }
	};

	GfxGPUBufferDesc vbDesc;
	vbDesc.size  = sizeof( vertices );
	vbDesc.type  = GFX_BUFFER_TYPE_DYNAMIC;
	vbDesc.usage = GFX_BUFFER_USAGE_DYNAMIC_DRAW;


	glGenVertexArrays( 1, &emptyVAO );
	glCreateBuffers( 1, &vb );
	glNamedBufferStorage( vb, sizeof( Vertex ) * 3, vertices, GL_DYNAMIC_STORAGE_BIT );
	//vb = gfxCreateGPUBuffer( 0, &vbDesc );
	// gfxBufferSubData( vb, vertices, sizeof( vertices ) );
	// glNamedBufferSubData( vb, 0, sizeof( vertices ), vertices );


	glBindVertexArray( emptyVAO );
}

int main()
{
	if ( !initWindow() )
		return 1;

	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );
	
	gfxLoadOpenGL( glfwGetProcAddress );
	gfxViewport( 0, 0, 640, 480 );

	createShaders();
	createVertexData();

	gfxBindPipeline( pipeline );
	glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0, vb );

	while ( !glfwWindowShouldClose( window ) )
	{
		gfxSetClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		gfxClearRenderTarget( GFX_CLEAR_MASK_COLOR );

		glDrawArrays( GL_TRIANGLES, 0, 3 );

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	deinitWindow();

	return 0;
}