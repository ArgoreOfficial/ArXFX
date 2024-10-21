#include "gfx_opengl.h"

#include "../gfx.h"

#include <glad/glad.h>
#include <malloc.h>
#include <memory.h>

static GLenum getGlBufferEnum( eGfxGPUBufferType _type )
{
	switch( _type )
	{
	case GFX_BUFFER_TYPE_VERTEX:  return GL_ARRAY_BUFFER;         break;
	case GFX_BUFFER_TYPE_INDEX:   return GL_ELEMENT_ARRAY_BUFFER; break;
	case GFX_BUFFER_TYPE_UNIFORM: return GL_UNIFORM_BUFFER;       break;
	case GFX_BUFFER_TYPE_DYNAMIC: return GL_SHADER_STORAGE_BUFFER; break;
	}

	return GL_NONE;
}

static GLenum getGlBufferUsage( eGfxGPUBufferUsage _usage )
{
	switch( _usage )
	{
	case GFX_BUFFER_USAGE_STATIC_DRAW:  return GL_STATIC_DRAW; break;
	case GFX_BUFFER_USAGE_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW; break;
	}

	return GL_NONE;
}

void gfxViewport_opengl( int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
}

void gfxSetClearColor_opengl( float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );
}

void gfxClearRenderTarget_opengl( GfxClearMask _mask )
{
	GLbitfield mask = 0;
	if ( _mask && GFX_CLEAR_MASK_COLOR ) mask |= GL_COLOR_BUFFER_BIT;
	if ( _mask && GFX_CLEAR_MASK_DEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

	glClear( mask );
}

GfxGPUBufferID gfxCreateGPUBuffer_opengl( GfxGPUBufferID _bufferID, sGfxGPUBufferDesc* _desc )
{
	if( _bufferID == 0 )
		_bufferID = 1; // get new id

	sGfxGPUBuffer* buffer = malloc( sizeof( sGfxGPUBuffer ) );// = m_gpuBuffers.get( _bufferID );
	memset( buffer, 0, sizeof( sGfxGPUBuffer ) );

	if( buffer == NULL )
		return 0;

	buffer->type  = _desc->type;
	buffer->usage = _desc->usage;
	buffer->name  = _desc->name;

	GLenum target = getGlBufferEnum( buffer->type );

	glCreateBuffers( 1, &buffer->handle );

	GLenum usage = getGlBufferUsage( buffer->usage );
	buffer->size = _desc->size;

	glNamedBufferData( buffer->handle, _desc->size, 0, usage );

	buffer->complete = 1;

	return _bufferID;
}

void gfxLoadOpenGL( GLloadproc _loadProc )
{
	gladLoadGLLoader( _loadProc );

	gfxViewport = gfxViewport_opengl;
	gfxSetClearColor = gfxSetClearColor_opengl;
	gfxClearRenderTarget = gfxClearRenderTarget_opengl;
	gfxCreateGPUBuffer = gfxCreateGPUBuffer_opengl;
}

