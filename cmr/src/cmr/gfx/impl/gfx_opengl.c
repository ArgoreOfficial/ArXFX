#include "gfx_opengl.h"

#include "../gfx.h"

#include <glad/glad.h>

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#ifdef ARG_GFX_STACK_ALLOCATED_OBJECTS
#define OBJECT_ALLOC_FUNC( _handle, _buffer, _max ) \
static _handle allocate##_handle()                  \
{                                                   \
	for( size_t i = 0; i < _max; i++ )              \
		if( _buffer[ i ].handle == 0 )              \
			return i + 1;                           \
	return 0;                                       \
}

#define ARG_GFX_MAX_PROGRAMS 128
#define ARG_GFX_MAX_GPU_BUFFERS 128
#define ARG_GFX_MAX_PIPELINES 128

static ArgGfxProgramObject s_programObjects[ ARG_GFX_MAX_PROGRAMS ];
static ArgGfxBufferObject s_bufferObjects[ ARG_GFX_MAX_GPU_BUFFERS ];
static ArgGfxPipelineObject s_pipelineObjects[ ARG_GFX_MAX_PIPELINES ];
static ArgGfxPipeline s_currentlyBoundPipeline;

#define ARG_GFX_GET_PROGRAM( _program ) &s_programObjects[ _program - 1 ]
#define ARG_GFX_GET_PIPELINE( _pipeline ) &s_pipelineObjects[ _pipeline - 1 ]
#define ARG_GFX_GET_BUFFER( _buffer ) &s_bufferObjects[ _buffer - 1 ]

OBJECT_ALLOC_FUNC( ArgGfxProgram, s_programObjects, ARG_GFX_MAX_PROGRAMS )
OBJECT_ALLOC_FUNC( ArgGfxBuffer, s_bufferObjects, ARG_GFX_MAX_GPU_BUFFERS )
OBJECT_ALLOC_FUNC( ArgGfxPipeline, s_pipelineObjects, ARG_GFX_MAX_PIPELINES )


#endif // ARG_GFX_STACK_ALLOCATED_OBJECTS

void glMessageCallback( GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, GLchar const* _message, void const* _userData )
{
	printf( "%s\n", _message );
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferEnum( ArgGfxBufferType _type )
{
	switch( _type )
	{
	case ARG_GFX_BUFFER_TYPE_VERTEX:  return GL_ARRAY_BUFFER;         break;
	case ARG_GFX_BUFFER_TYPE_INDEX:   return GL_ELEMENT_ARRAY_BUFFER; break;
	case ARG_GFX_BUFFER_TYPE_UNIFORM: return GL_UNIFORM_BUFFER;       break;
	case ARG_GFX_BUFFER_TYPE_DYNAMIC: return GL_SHADER_STORAGE_BUFFER; break;
	}

	return GL_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferUsage( ArgGfxBufferUsage _usage )
{
	switch( _usage )
	{
	case ARG_GFX_BUFFER_USAGE_STATIC_DRAW:  return GL_STATIC_DRAW; break;
	case ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW; break;
	}

	return GL_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////

static void bindVertexLayout( ArgGfxVertexLayout* _pVertexLayout )
{
	int pointer = 0;
	for ( size_t i = 0; i < _pVertexLayout->numAttributes; i++ )
	{
		ArgGfxVertexAttrib* attrib = &_pVertexLayout->attributes[ i ];

		GLenum type = GL_NONE;
		switch ( attrib->type )
		{
		case ARG_FLOAT:        type = GL_FLOAT;        break;
		case ARG_INT:          type = GL_INT;          break;
		case ARG_UNSIGNED_INT: type = GL_UNSIGNED_INT; break;
		}
		
		glVertexAttribPointer( i, attrib->componentCount, type, attrib->normalized, _pVertexLayout->stride, pointer );
		glEnableVertexAttribArray( i );

		pointer += attrib->size;
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxViewport_opengl( int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxSetClearColor_opengl( float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxClearRenderTarget_opengl( ArgGfxClearMask _mask )
{
	GLbitfield mask = 0;
	if ( _mask && ARG_GFX_CLEAR_MASK_COLOR ) mask |= GL_COLOR_BUFFER_BIT;
	if ( _mask && ARG_GFX_CLEAR_MASK_DEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

	glClear( mask );
}

///////////////////////////////////////////////////////////////////////////////////////

ArgGfxProgram argGfxCreateProgram_opengl( ArgGfxProgram _program, ArgGfxProgramDesc* _desc )
{
	ArgGfxShaderProgramType type = _desc->type;
	const char* sourceStr = _desc->source;

#ifdef ARG_GFX_STACK_ALLOCATED_OBJECTS
	if( _program == 0 )
	{
		_program = allocateArgGfxProgram();

		if( _program == 0 ) // error
			return 0;
	}
#endif

	ArgGfxProgramObject* program = ARG_GFX_GET_PROGRAM( _program );
	program->type = type;
	
	GLenum glType = GL_NONE;
	{
		switch( type )
		{
		case ARG_GFX_SHADER_TYPE_FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
		case ARG_GFX_SHADER_TYPE_VERTEX:   glType = GL_VERTEX_SHADER;   break;
		}
	}

	program->handle = glCreateShaderProgramv( glType, 1, &sourceStr );

	int success = 0;
	char infoLog[ 512 ];
	glGetProgramiv( program->handle, GL_LINK_STATUS, &success );
	if( !success )
	{
		glGetProgramInfoLog( program->handle, 512, NULL, infoLog );
		printf( "Failed to link program\n %s \n", infoLog );
	}
	
	return _program;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgGfxPipeline argGfxCreatePipeline_opengl( ArgGfxPipeline _pipeline, ArgGfxPipelineDesc* _desc )
{
	if( _pipeline == 0 )
	{
		_pipeline = allocateArgGfxPipeline();
		if( _pipeline == 0 ) // error
			return 0;
	}
	ArgGfxPipelineObject* pPipeline = ARG_GFX_GET_PIPELINE( _pipeline );

	pPipeline->vertexProgram   = _desc->vertexProgram;
	pPipeline->fragmentProgram = _desc->fragmentProgram;
	pPipeline->pVertexLayout   = _desc->pVertexLayout;

	glCreateProgramPipelines( 1, &pPipeline->handle );

	if( pPipeline->handle == 0 )
		return 0;
	
	ArgGfxProgramObject* vs = ARG_GFX_GET_PROGRAM( _desc->vertexProgram );
	ArgGfxProgramObject* fs = ARG_GFX_GET_PROGRAM( _desc->fragmentProgram );

	glUseProgramStages( pPipeline->handle, GL_VERTEX_SHADER_BIT, vs->handle );
	glUseProgramStages( pPipeline->handle, GL_FRAGMENT_SHADER_BIT, fs->handle );

	return _pipeline;
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxBindPipeline_opengl( ArgGfxPipeline _pipeline )
{
	s_currentlyBoundPipeline = _pipeline;

	ArgGfxPipelineObject* pPipeline = ARG_GFX_GET_PIPELINE( _pipeline );
	glBindProgramPipeline( pPipeline->handle );
}

///////////////////////////////////////////////////////////////////////////////////////

ArgGfxBuffer argGfxCreateBuffer_opengl( ArgGfxBuffer _buffer, ArgGfxBufferDesc* _desc )
{
	ArgGfxBufferObject* pBuffer = NULL;

#if defined( ARG_GFX_STACK_ALLOCATED_OBJECTS )
	if( _buffer == 0 )
	{
		_buffer = allocateArgGfxBuffer();
		if( _buffer == 0 ) // error
			return 0;
	}

	pBuffer = &s_bufferObjects[ _buffer - 1 ];
#elif defined( ARG_GFX_STACK_ALLOCATED_OBJECTS )
	if( _buffer == 0 )
	{
		buffer = malloc( sizeof( ArgGfxBufferObject ) );
		_buffer = &buffer;
	}
#endif

	pBuffer->type = _desc->type;
	pBuffer->usage = _desc->usage;
	pBuffer->size = _desc->size;
	
	GLenum usage = getGlBufferUsage( pBuffer->usage );

	glCreateBuffers( 1, &pBuffer->handle );
	glNamedBufferData( pBuffer->handle, _desc->size, 0, usage );

	return _buffer;
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxBindBuffer_opengl( ArgGfxBuffer _buffer )
{
	ArgGfxBufferObject* pBuffer = ARG_GFX_GET_BUFFER( _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBuffer( target, pBuffer->handle );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxBindBufferIndex_opengl( ArgGfxBuffer _buffer, int32_t _bindingIndex )
{
	ArgGfxBufferObject* pBuffer = ARG_GFX_GET_BUFFER( _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBufferBase( target, _bindingIndex, pBuffer->handle );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxBufferData_opengl( ArgGfxBuffer _buffer, void* _pData, size_t _size )
{
	ArgGfxBufferObject* pBuffer = ARG_GFX_GET_BUFFER( _buffer );
	GLenum usage = getGlBufferUsage( pBuffer->usage );
	glNamedBufferData( pBuffer->handle, _size, _pData, usage );
}

void argGfxBufferSubData_opengl( ArgGfxBuffer _buffer, void* _pData, size_t _size, size_t _base )
{
	ArgGfxBufferObject* pBuffer = ARG_GFX_GET_BUFFER( _buffer );
	glNamedBufferSubData( pBuffer->handle, _base, _size, _pData );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxDraw_opengl( uint32_t _firstVertex, uint32_t _numVertices )
{
	ArgGfxPipelineObject* pPipeline = ARG_GFX_GET_PIPELINE( s_currentlyBoundPipeline );
	bindVertexLayout( pPipeline->pVertexLayout );

	glDrawArrays( GL_TRIANGLES, _firstVertex, _numVertices );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxDrawIndexed_opengl( uint32_t _numIndices )
{
	ArgGfxPipelineObject* pPipeline = ARG_GFX_GET_PIPELINE( s_currentlyBoundPipeline );
	bindVertexLayout( pPipeline->pVertexLayout );

	glDrawElements( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0 );
}

///////////////////////////////////////////////////////////////////////////////////////

void argGfxLoadOpenGL( GLloadproc _loadProc )
{
	gladLoadGLLoader( _loadProc );

	glEnable( GL_DEBUG_OUTPUT );
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
	glDebugMessageCallback( glMessageCallback, NULL );
	//glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );

#ifdef TST_IMPL
	printf( "test\n" );
#endif

	argGfxViewport      = argGfxViewport_opengl;
	argGfxSetClearColor = argGfxSetClearColor_opengl;
	
	argGfxClearRenderTarget = argGfxClearRenderTarget_opengl;

	argGfxCreateProgram = argGfxCreateProgram_opengl;
	
	argGfxCreatePipeline = argGfxCreatePipeline_opengl;
	argGfxBindPipeline   = argGfxBindPipeline_opengl;

	argGfxCreateBuffer    = argGfxCreateBuffer_opengl;
	argGfxBufferData      = argGfxBufferData_opengl;
	argGfxBufferSubData   = argGfxBufferSubData_opengl;
	argGfxBindBufferIndex = argGfxBindBufferIndex_opengl;
	argGfxBindBuffer      = argGfxBindBuffer_opengl;

	argGfxDraw        = argGfxDraw_opengl;
	argGfxDrawIndexed = argGfxDrawIndexed_opengl;
}


