#include <ARG/gfx.h>

#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ARG_GFX_MAX_GPU_BUFFERS 128
#define ARG_GFX_MAX_PIPELINES 128
#define ARG_GFX_MAX_PROGRAMS 128

#define ARG_GET_OBJECT( _container, _handle ) _handle 

#define ARG_GFX_GET_PROGRAM( _program ) s_programObjects + ( _program - 1 )
#define ARG_GFX_GET_PIPELINE( _pipeline ) s_pipelineObjects + ( _pipeline - 1 )
#define ARG_GFX_GET_BUFFER( _buffer ) s_bufferObjects + ( _buffer - 1 )

#define ARG_GFX_OBJECT_ALLOC_FUNC( _object, _buffer, _max ) \
static _object argGfxAlloc##_object( ArgGfxContext _ctx )   \
{                                                           \
	for( size_t i = 0; i < _max; i++ )                      \
		if( _ctx->_buffer[ i ].handle == 0 )                \
			return &_ctx->_buffer[i];                       \
	return 0;                                               \
} \
static ArgResult argGfxDealloc##_object( ArgGfxContext _ctx, _object _obj ) \
{ \
	memset( _obj, 0, sizeof( _ctx->_buffer[ 0 ] ) ); \
}

typedef void* ( *GLloadproc )( const char* name );

struct ArgGfxProgram_t
{
	GLuint handle;
	ArgGfxShaderProgramType type;

	GLenum glType;
};

struct ArgGfxPipeline_t
{
	GLuint handle;
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
	ArgGfxVertexLayout* pVertexLayout;
};

struct ArgGfxBuffer_t
{
	GLuint handle;

	ArgGfxBufferType type;
	ArgGfxBufferUsage usage;

	GLenum glType;
	GLenum glUsage;

	uint32_t count;
	uint32_t stride;
	int32_t  size;

	ArgHandle blockIndex;
	GLuint bindingIndex;
};


struct ArgGfxContext_t
{
	uint8_t initialized;
	int width;
	int height;

	struct ArgGfxProgram_t programObjects[ ARG_GFX_MAX_PROGRAMS ];
	struct ArgGfxBuffer_t bufferObjects[ ARG_GFX_MAX_GPU_BUFFERS ];
	struct ArgGfxPipeline_t pPipelines[ ARG_GFX_MAX_PIPELINES ];
	ArgGfxPipeline currentlyBoundPipeline;

	unsigned int m_VAO;
};

struct ArgGfxContext_t g_ctxs[ 3 ];

ARG_GFX_OBJECT_ALLOC_FUNC( ArgGfxProgram,  programObjects,  ARG_GFX_MAX_PROGRAMS )
ARG_GFX_OBJECT_ALLOC_FUNC( ArgGfxPipeline, pPipelines, ARG_GFX_MAX_PIPELINES )
ARG_GFX_OBJECT_ALLOC_FUNC( ArgGfxBuffer,   bufferObjects,   ARG_GFX_MAX_GPU_BUFFERS )


///////////////////////////////////////////////////////////////////////////////////////

static void glMessageCallback( GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, GLchar const* _message, void const* _userData )
{
	printf( "%s\n", _message );
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferEnum( ArgGfxBufferType _type )
{
	switch ( _type )
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
	switch ( _usage )
	{
	case ARG_GFX_BUFFER_USAGE_STATIC_DRAW:  return GL_STATIC_DRAW; break;
	case ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW; break;
	}

	return GL_NONE;
}

ArgResult argGfxInit()
{
	gladLoadGLLoader( (GLloadproc)glfwGetProcAddress );

	glEnable( GL_DEBUG_OUTPUT );
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
	glDebugMessageCallback( glMessageCallback, NULL );
	glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );

	// glEnable( GL_DEPTH_TEST );
	// glDepthFunc( GL_LESS );

	memset( g_ctxs, 0, sizeof( g_ctxs ) );
	return ARG_SUCESS;
}

ArgResult argGfxCreateContext( ArgGfxContext* _pCtx )
{
	struct ArgGfxContext_t* ctx = NULL;
	for ( size_t i = 0; i < 3; i++ )
	{
		if ( g_ctxs[ i ].initialized != 0 )
			continue;

		ctx = &g_ctxs[ i ];
		break;
	}

	if ( ctx == NULL )
		return ARG_ERROR_OUT_OF_MEMORY;

	ctx->initialized = true;

	glCreateVertexArrays( 1, &ctx->m_VAO );
	
	*_pCtx = ctx;
	return ARG_SUCESS;
}

ArgResult argGfxViewport( ArgGfxContext _ctx, int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
	
	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxSetClearColor( ArgGfxContext _ctx, float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxClearRenderTarget( ArgGfxContext _ctx, ArgGfxClearMask _mask )
{
	GLbitfield mask = 0;
	if ( _mask && ARG_GFX_CLEAR_MASK_COLOR ) mask |= GL_COLOR_BUFFER_BIT;
	if ( _mask && ARG_GFX_CLEAR_MASK_DEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

	glClear( mask );
	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxSetFillMode( ArgGfxContext _ctx, ArgGfxFillMode _mode )
{
	switch ( _mode )
	{
	case ARG_GFX_FILL_MODE_SOLID:     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );  break;
	case ARG_GFX_FILL_MODE_WIREFRAME: glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );  break;
	case ARG_GFX_FILL_MODE_POINTS:    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ); break;
	}
	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxCreateProgram( ArgGfxContext _ctx, ArgGfxProgramDesc* _desc, ArgGfxProgram* _pProgram )
{
	ArgGfxShaderProgramType type = _desc->type;
	const char* sourceStr = _desc->source;

	*_pProgram = argGfxAllocArgGfxProgram( _ctx );

	if ( *_pProgram == 0 ) // error
		return ARG_ERROR_OUT_OF_MEMORY;

	struct ArgGfxProgram_t* program = ARG_GET_OBJECT( _ctx->programObjects, _pProgram );

	GLenum glType = GL_NONE;
	{
		switch ( type )
		{
		case ARG_GFX_SHADER_TYPE_FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
		case ARG_GFX_SHADER_TYPE_VERTEX:   glType = GL_VERTEX_SHADER;   break;
		}
	}

	program->type = type;
	program->glType = glType;

	program->handle = glCreateShaderProgramv( glType, 1, &sourceStr );

	int success = 0;
	char infoLog[ 512 ];
	glGetProgramiv( program->handle, GL_LINK_STATUS, &success );
	if ( !success )
	{
		glGetProgramInfoLog( program->handle, 512, NULL, infoLog );
		printf( "Failed to link program\n %s \n", infoLog );
	}

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDestroyProgram( ArgGfxContext _ctx, ArgGfxProgram _program )
{
	struct ArgGfxProgram_t* pProgram = ARG_GET_OBJECT( _ctx->programObjects, _program );
	glDeleteProgram( pProgram->handle );
	argGfxDeallocArgGfxProgram( _ctx, _program );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxCreatePipeline( ArgGfxContext _ctx, ArgGfxPipelineDesc* _desc, ArgGfxPipeline* _pPipeline )
{
	*_pPipeline = argGfxAllocArgGfxPipeline( _ctx );
	if ( *_pPipeline == 0 ) // error
		return ARG_ERROR_OUT_OF_MEMORY;
	
	struct ArgGfxPipeline_t* pPipeline = ARG_GET_OBJECT( _ctx->pPipelines, *_pPipeline );

	pPipeline->vertexProgram = _desc->vertexProgram;
	pPipeline->fragmentProgram = _desc->fragmentProgram;
	pPipeline->pVertexLayout = _desc->pVertexLayout;

	glCreateProgramPipelines( 1, &pPipeline->handle );

	if ( pPipeline->handle == 0 )
		return ARG_ERROR_UNKNOWN;

	struct ArgGfxProgram_t* vs = ARG_GET_OBJECT( _ctx->programObjects, _desc->vertexProgram );
	struct ArgGfxProgram_t* fs = ARG_GET_OBJECT( _ctx->programObjects, _desc->fragmentProgram );

	glUseProgramStages( pPipeline->handle, GL_VERTEX_SHADER_BIT, vs->handle );
	glUseProgramStages( pPipeline->handle, GL_FRAGMENT_SHADER_BIT, fs->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDestroyPipeline( ArgGfxContext _ctx, ArgGfxPipeline _pipeline )
{
	struct ArgGfxPipeline_t* pPipeline = ARG_GET_OBJECT( _ctx->pPipelines, _pipeline );
	glDeleteProgramPipelines( 1, &pPipeline->handle );
	argGfxDeallocArgGfxPipeline( _ctx, _pipeline );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBindPipeline( ArgGfxContext _ctx, ArgGfxPipeline _pipeline )
{
	_ctx->currentlyBoundPipeline = _pipeline;
	struct ArgGfxPipeline_t* pPipeline = ARG_GET_OBJECT( _ctx->pPipelines, _pipeline );
	glBindProgramPipeline( pPipeline->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDraw( ArgGfxContext _ctx, uint32_t _firstVertex, uint32_t _numVertices )
{
	glDrawArrays( GL_TRIANGLES, _firstVertex, _numVertices );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDrawIndexed( ArgGfxContext _ctx, uint32_t _numIndices )
{
	glDrawElements( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0 );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDrawIndexedInstanced( ArgGfxContext _ctx, uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
	glDrawElementsInstancedBaseVertex( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0, _numInstances, _baseVertex );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBindVertexLayout( ArgGfxContext _ctx, ArgGfxVertexLayout* _pVertexLayout )
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

		glVertexAttribPointer( i, attrib->componentCount, type, attrib->normalized, _pVertexLayout->stride, (const void*)pointer );
		glEnableVertexAttribArray( i );

		pointer += attrib->size;
	}

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxCreateBuffer( ArgGfxContext _ctx, ArgGfxBufferDesc* _desc, ArgGfxBuffer* _pBuffer )
{
	*_pBuffer = argGfxAllocArgGfxBuffer( _ctx );
	if ( *_pBuffer == 0 )
		return ARG_ERROR_OUT_OF_MEMORY;
	
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _pBuffer );

	pBuffer->type = _desc->type;
	pBuffer->usage = _desc->usage;
	pBuffer->size = _desc->size;

	GLenum usage = getGlBufferUsage( pBuffer->usage );

	glCreateBuffers( 1, &pBuffer->handle );
	glNamedBufferData( pBuffer->handle, _desc->size, 0, usage );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxDestroyBuffer( ArgGfxContext _ctx, ArgGfxBuffer _buffer )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	glDeleteBuffers( 1, &pBuffer->handle );
	argGfxDeallocArgGfxBuffer( _ctx, _buffer );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBindBuffer( ArgGfxContext _ctx, ArgGfxBuffer _buffer )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBuffer( target, pBuffer->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBindBufferIndex( ArgGfxContext _ctx, ArgGfxBuffer _buffer, int32_t _bindingIndex )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBufferBase( target, _bindingIndex, pBuffer->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBufferData( ArgGfxContext _ctx, ArgGfxBuffer _buffer, void* _pData, size_t _size )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum usage = getGlBufferUsage( pBuffer->usage );
	glNamedBufferData( pBuffer->handle, _size, _pData, usage );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBufferSubData( ArgGfxContext _ctx, ArgGfxBuffer _buffer, void* _pData, size_t _size, size_t _base )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	glNamedBufferSubData( pBuffer->handle, _base, _size, _pData );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxCopyBufferSubData( ArgGfxContext _ctx, ArgGfxBuffer _readBuffer, ArgGfxBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
	struct ArgGfxBuffer_t* pReadBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _readBuffer );
	struct ArgGfxBuffer_t* pWriteBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _writeBuffer );

	glCopyNamedBufferSubData( pReadBuffer->handle, pWriteBuffer->handle, _readOffset, _writeOffset, _size );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

ArgResult argGfxBindVertexBuffer( ArgGfxContext _ctx, ArgGfxBuffer _vertexBuffer )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _vertexBuffer );
	printf( "argGfxBindVertexBuffer is not implemented\n" );

	// bindBufferIndex( m_vertexBuffer, SbVertices.bindingIndex.value );
	// bindBuffer( m_indexBuffer );

	return ARG_SUCESS;
}

#ifdef __cplusplus
}
#endif