#include "gfx_opengl.h"

#include "../gfx.h"

#include <glad/glad.h>

#include <malloc.h>
#include <memory.h>
#include <stdio.h>

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

GfxProgram* gfxCreateProgram_opengl( GfxProgramDesc* _desc )
{
	GfxShaderProgramType type = _desc->type;
	const char* sourceStr = _desc->source;

	GfxProgram* program = malloc( sizeof( GfxProgram ) );
	program->type = type;
	
	GLenum glType = GL_NONE;
	{
		switch( type )
		{
		case WV_SHADER_TYPE_FRAGMENT: glType = GL_FRAGMENT_SHADER; break;
		case WV_SHADER_TYPE_VERTEX:   glType = GL_VERTEX_SHADER;   break;
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

	GLint numActiveResources;
	glGetProgramInterfaceiv( program.handle, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numActiveResources );

	for( GLuint i = 0; i < numActiveResources; i++ )
	{
		GLenum props[ 1 ] = { GL_NAME_LENGTH };
		GLint res[ 1 ];
		glGetProgramResourceiv( program.handle, GL_UNIFORM_BLOCK, i, std::size( props ), props, std::size( res ), nullptr, res );

		std::string name( (GLuint)res[ 0 ] - 1, '\0' );
		glGetProgramResourceName( program.handle, GL_UNIFORM_BLOCK, i, name.capacity() + 1, nullptr, name.data() );

		// create uniform buffer

		GfxGPUBufferDesc ubDesc;
		ubDesc.name = name;
		ubDesc.type = GFX_BUFFER_TYPE_UNIFORM;
		ubDesc.usage = GFX_BUFFER_USAGE_DYNAMIC_DRAW;

		bufferBindingIndex_t index;
		if( m_uniformBindingNameMap.contains( name ) )
		{
			index = m_uniformBindingNameMap.at( name );
			m_uniformBindingIndices.get( index )++; // increase num users
		}
		else
		{
			index = m_uniformBindingIndices.allocate();
			m_uniformBindingNameMap[ name ] = index;
		}

		wv::Handle blockIndex = glGetUniformBlockIndex( program.handle, name.c_str() );
		glGetActiveUniformBlockiv( program.handle, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &ubDesc.size );

		GPUBufferID bufID = createGPUBuffer( 0, &ubDesc );
		sGPUBuffer& buf = m_gpuBuffers.get( bufID );

		buf.bindingIndex = index;
		buf.blockIndex = blockIndex;

		//WV_ASSERT_GL( glBindBufferBase( GL_UNIFORM_BUFFER, buf.bindingIndex.value, buf.handle ) );
		glUniformBlockBinding( program.handle, buf.blockIndex, buf.bindingIndex.value );

		program.shaderBuffers.push_back( bufID );
	}


	GLint numActiveSSBOs;
	glGetProgramInterfaceiv( program.handle, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES, &numActiveSSBOs );
	for( GLuint i = 0; i < numActiveSSBOs; i++ )
	{
		GLenum props[ 1 ] = { GL_NAME_LENGTH };
		GLint res[ 1 ];
		glGetProgramResourceiv( program.handle, GL_SHADER_STORAGE_BLOCK, i, std::size( props ), props, std::size( res ), nullptr, res );

		std::string name( (GLuint)res[ 0 ] - 1, '\0' );
		glGetProgramResourceName( program.handle, GL_SHADER_STORAGE_BLOCK, i, name.capacity() + 1, nullptr, name.data() );

		// create ssbo

		sGPUBufferDesc ubDesc;
		ubDesc.name = name;
		ubDesc.type = WV_BUFFER_TYPE_DYNAMIC;
		ubDesc.usage = WV_BUFFER_USAGE_DYNAMIC_DRAW;
		ubDesc.size = 0;

		GPUBufferID bufID = createGPUBuffer( 0, &ubDesc );
		sGPUBuffer& buf = m_gpuBuffers.get( bufID );

		buf.bindingIndex = m_ssboBindingIndices.allocate();
		buf.blockIndex = glGetProgramResourceIndex( program.handle, GL_SHADER_STORAGE_BLOCK, name.data() );

		glBindBufferBase( GL_SHADER_STORAGE_BUFFER, buf.bindingIndex.value, buf.handle );
		glShaderStorageBlockBinding( program.handle, buf.blockIndex, buf.bindingIndex.value );

		program.shaderBuffers.push_back( bufID );
	}

	return _programID;
}

GfxGPUBufferID gfxCreateGPUBuffer_opengl( GfxGPUBufferID _bufferID, GfxGPUBufferDesc* _desc )
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

