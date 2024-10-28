#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <gfx/gfx.h>
#include <gfx/impl/gfx_opengl.h>
#include <glad/glad.h>

GLFWwindow* window;

GfxPipeline pipeline;
GfxGPUBuffer vb;

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

void createShaders()
{
	GfxProgramDesc vsDesc;
	vsDesc.type = GFX_SHADER_TYPE_VERTEX;
	vsDesc.source =
		"#version 330\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()"
		"{"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
		"}";
	
	GfxProgramDesc fsDesc;
	fsDesc.type = GFX_SHADER_TYPE_FRAGMENT;
	fsDesc.source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()"
		"{"
			"FragColor = vec4( 1.0f, 0.5f, 0.2f, 1.0f );"
		"}";

	
	GfxProgram vs = gfxCreateProgram( 0, &vsDesc );
	GfxProgram fs = gfxCreateProgram( 0, &fsDesc );

	GfxPipelineDesc pipelineDesc;
	pipelineDesc.fragmentProgram = fs;
	pipelineDesc.vertexProgram = vs;
	pipelineDesc.pVertexLayout = NULL;
	pipeline = gfxCreatePipeline( 0, &pipelineDesc );
}

void createVertexData()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	GfxGPUBufferDesc vbDesc;
	vbDesc.size  = sizeof( vertices );
	vbDesc.type  = GFX_BUFFER_TYPE_VERTEX;
	vbDesc.usage = GFX_BUFFER_USAGE_STATIC_DRAW;

	vb = gfxCreateGPUBuffer( 0, &vbDesc );
	// gfxBufferSubData( vb, vertices, sizeof( vertices ) );
	glNamedBufferSubData( vb, 0, sizeof( vertices ), vertices );
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
	glBindBuffer( GL_ARRAY_BUFFER, vb );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );


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