
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef asd
#ifdef __cplusplus
extern "C" {
#endif


typedef void* ( *GLloadproc )( const char* name );

///////////////////////////////////////////////////////////////////////////////////////

static void glMessageCallback( GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, GLchar const* _message, void const* _userData )
{
	printf( "%s\n", _message );
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferEnum( BufferType _type )
{
	switch ( _type )
	{
	case kVERTEX:  return GL_ARRAY_BUFFER;         break;
	case kINDEX:   return GL_ELEMENT_ARRAY_BUFFER; break;
	case kUNIFORM: return GL_UNIFORM_BUFFER;       break;
	case kDYNAMIC: return GL_SHADER_STORAGE_BUFFER; break;
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

Result argGfxInit()
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

Result argGfxCreateContext( Context* _pCtx )
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

Result argGfxViewport( Context _ctx, int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
	
	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxSetClearColor( Context _ctx, float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxClearRenderTarget( Context _ctx, ArgGfxClearMask _mask )
{
	GLbitfield mask = 0;
	if ( _mask && ARG_GFX_CLEAR_MASK_COLOR ) mask |= GL_COLOR_BUFFER_BIT;
	if ( _mask && ARG_GFX_CLEAR_MASK_DEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

	glClear( mask );
	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxSetFillMode( Context _ctx, ArgGfxFillMode _mode )
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

Result argGfxCreateProgram( Context _ctx, ProgramDesc* _desc, ShaderModule* _pProgram )
{
	ShaderProgramType type = _desc->type;
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

Result argGfxDestroyProgram( Context _ctx, ShaderModule _program )
{
	struct ArgGfxProgram_t* pProgram = ARG_GET_OBJECT( _ctx->programObjects, _program );
	glDeleteProgram( pProgram->handle );
	argGfxDeallocArgGfxProgram( _ctx, _program );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxCreatePipeline( Context _ctx, ShaderPipelineDesc* _desc, ShaderPipeline* _pPipeline )
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

Result argGfxDestroyPipeline( Context _ctx, ShaderPipeline _pipeline )
{
	struct ArgGfxPipeline_t* pPipeline = ARG_GET_OBJECT( _ctx->pPipelines, _pipeline );
	glDeleteProgramPipelines( 1, &pPipeline->handle );
	argGfxDeallocArgGfxPipeline( _ctx, _pipeline );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBindPipeline( Context _ctx, ShaderPipeline _pipeline )
{
	_ctx->currentlyBoundPipeline = _pipeline;
	struct ArgGfxPipeline_t* pPipeline = ARG_GET_OBJECT( _ctx->pPipelines, _pipeline );
	glBindProgramPipeline( pPipeline->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxDraw( Context _ctx, uint32_t _firstVertex, uint32_t _numVertices )
{
	glDrawArrays( GL_TRIANGLES, _firstVertex, _numVertices );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxDrawIndexed( Context _ctx, uint32_t _numIndices )
{
	glDrawElements( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0 );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxDrawIndexedInstanced( Context _ctx, uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
	glDrawElementsInstancedBaseVertex( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0, _numInstances, _baseVertex );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBindVertexLayout( Context _ctx, VertexLayout* _pVertexLayout )
{
	int pointer = 0;
	for ( size_t i = 0; i < _pVertexLayout->numAttributes; i++ )
	{
		VertexAttrib* attrib = &_pVertexLayout->attributes[ i ];

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

Result argGfxCreateBuffer( Context _ctx, ArgGfxBufferDesc* _desc, Buffer* _pBuffer )
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

Result argGfxDestroyBuffer( Context _ctx, Buffer _buffer )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	glDeleteBuffers( 1, &pBuffer->handle );
	argGfxDeallocArgGfxBuffer( _ctx, _buffer );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBindBuffer( Context _ctx, Buffer _buffer )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBuffer( target, pBuffer->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBindBufferIndex( Context _ctx, Buffer _buffer, int32_t _bindingIndex )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum target = getGlBufferEnum( pBuffer->type );
	glBindBufferBase( target, _bindingIndex, pBuffer->handle );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBufferData( Context _ctx, Buffer _buffer, void* _pData, size_t _size )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	GLenum usage = getGlBufferUsage( pBuffer->usage );
	glNamedBufferData( pBuffer->handle, _size, _pData, usage );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBufferSubData( Context _ctx, Buffer _buffer, void* _pData, size_t _size, size_t _base )
{
	struct ArgGfxBuffer_t* pBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _buffer );
	glNamedBufferSubData( pBuffer->handle, _base, _size, _pData );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxCopyBufferSubData( Context _ctx, Buffer _readBuffer, Buffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
	struct ArgGfxBuffer_t* pReadBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _readBuffer );
	struct ArgGfxBuffer_t* pWriteBuffer = ARG_GET_OBJECT( _ctx->bufferObjects, _writeBuffer );

	glCopyNamedBufferSubData( pReadBuffer->handle, pWriteBuffer->handle, _readOffset, _writeOffset, _size );

	return ARG_SUCESS;
}

///////////////////////////////////////////////////////////////////////////////////////

Result argGfxBindVertexBuffer( Context _ctx, Buffer _vertexBuffer )
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

#endif
