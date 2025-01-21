#include "OpenGLRenderer.h"


#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef void* ( *GLloadproc )( const char* name );

///////////////////////////////////////////////////////////////////////////////////////

static afx::ILowLevelRenderer* openGLRendererAllocator( void* _pUserData ) {
    return new afx::OpenGLRenderer();
}
afx::ILowLevelRenderer::Entry afx::OpenGLRenderer::g_register{ "OpenGL", openGLRendererAllocator };

///////////////////////////////////////////////////////////////////////////////////////

static void glMessageCallback( GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, GLchar const* _message, void const* _userData )
{
    printf( "%s\n", _message );
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferEnum( afx::BufferType _type )
{
    switch( _type )
    {
    case afx::BufferType::kVERTEX:  return GL_ARRAY_BUFFER;         break;
    case afx::BufferType::kINDEX:   return GL_ELEMENT_ARRAY_BUFFER; break;
    case afx::BufferType::kUNIFORM: return GL_UNIFORM_BUFFER;       break;
    case afx::BufferType::kDYNAMIC: return GL_SHADER_STORAGE_BUFFER; break;
    }

    return GL_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////

static GLenum getGlBufferUsage( afx::BufferUsage _usage )
{
    switch( _usage )
    {
    case afx::BufferUsage::kSTATIC_DRAW:  return GL_STATIC_DRAW; break;
    case afx::BufferUsage::kDYNAMIC_DRAW: return GL_DYNAMIC_DRAW; break;
    }

    return GL_NONE;
}

///////////////////////////////////////////////////////////////////////////////////////

namespace afx {

Result OpenGLRenderer::init()
{
    gladLoadGLLoader( (GLloadproc)glfwGetProcAddress );

    glEnable( GL_DEBUG_OUTPUT );
    glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
    glDebugMessageCallback( glMessageCallback, NULL );
    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );

    // glEnable( GL_DEPTH_TEST );
    // glDepthFunc( GL_LESS );

    // glCreateVertexArrays( 1, &m_VAO );

    return ARG_SUCESS;
}

Result OpenGLRenderer::viewport( int _x, int _y, int _width, int _height )
{
    glViewport( _x, _y, _width, _height );

    return ARG_SUCESS;
}

Result OpenGLRenderer::setClearColor( float _r, float _g, float _b, float _a )
{
    glClearColor( _r, _g, _b, _a );

    return ARG_SUCESS;
}

Result OpenGLRenderer::clearRenderTarget( ClearMask _mask )
{
    GLbitfield mask = 0;
    if( _mask && ClearMask::kCOLOR ) mask |= GL_COLOR_BUFFER_BIT;
    if( _mask && ClearMask::kDEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

    glClear( mask );
    return ARG_SUCESS;
}

Result OpenGLRenderer::setFillMode( FillMode _mode )
{
    switch( _mode )
    {
    case FillMode::kSOLID:     glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );  break;
    case FillMode::kWIREFRAME: glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );  break;
    case FillMode::kPOINTS:    glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ); break;
    }
    return ARG_SUCESS;
}

Result OpenGLRenderer::draw( uint32_t _firstVertex, uint32_t _numVertices )
{
    glDrawArrays( GL_TRIANGLES, _firstVertex, _numVertices );

    return ARG_SUCESS;
}

Result OpenGLRenderer::drawIndexed( uint32_t _numIndices )
{
    glDrawElements( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0 );

    return ARG_SUCESS;
}

Result OpenGLRenderer::drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
    glDrawElementsInstancedBaseVertex( GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0, _numInstances, _baseVertex );

    return ARG_SUCESS;
}

Result OpenGLRenderer::createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram )
{
    ShaderModuleType type = _desc->type;
    const char* sourceStr = _desc->source;
    ShaderModule program{};

    GLenum glType = GL_NONE;
    {
        switch( type )
        {
        case ShaderModuleType::kFRAGMENT: glType = GL_FRAGMENT_SHADER; break;
        case ShaderModuleType::kVERTEX:   glType = GL_VERTEX_SHADER;   break;
        }
    }

    program.type = type;
    program.glType = glType;

    program.handle = glCreateShaderProgramv( glType, 1, &sourceStr );

    int success = 0;
    char infoLog[ 512 ];
    glGetProgramiv( program.handle, GL_LINK_STATUS, &success );
    if( !success )
    {
        glGetProgramInfoLog( program.handle, 512, NULL, infoLog );
        printf( "Failed to link program\n %s \n", infoLog );
    }

    *_pProgram = m_shaderModules.emplace( program );
    if( *_pProgram == 0 ) // error
        return ARG_ERROR_OUT_OF_MEMORY;

    return ARG_SUCESS;
}

Result OpenGLRenderer::destroyProgram( ShaderModuleID _program )
{
    ShaderModule& program = m_shaderModules.at( _program );
    glDeleteProgram( program.handle );
    m_shaderModules.erase( _program );

    return ARG_SUCESS;
}

Result OpenGLRenderer::createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline )
{
    ShaderPipeline pipeline{}; // = ARG_GET_OBJECT( _ctx->pPipelines, *_pPipeline );
    
    pipeline.vertexProgram   = _desc->vertexProgram;
    pipeline.fragmentProgram = _desc->fragmentProgram;
    pipeline.pVertexLayout   = _desc->pVertexLayout;

    glCreateProgramPipelines( 1, &pipeline.handle );

    if( pipeline.handle == 0 )
        return ARG_ERROR_UNKNOWN;

    ShaderModule& vs = m_shaderModules.at( _desc->vertexProgram );
    ShaderModule& fs = m_shaderModules.at( _desc->fragmentProgram );

    glUseProgramStages( pipeline.handle, GL_VERTEX_SHADER_BIT, vs.handle );
    glUseProgramStages( pipeline.handle, GL_FRAGMENT_SHADER_BIT, fs.handle );

    *_pPipeline = m_shaderPipelines.emplace( pipeline );
    if( *_pPipeline == 0 )
        return ARG_ERROR_OUT_OF_MEMORY;

    return ARG_SUCESS;
}

Result OpenGLRenderer::destroyPipeline( ShaderPipelineID _pipeline )
{
    ShaderPipeline& pipeline = m_shaderPipelines.at( _pipeline );
    glDeleteProgramPipelines( 1, &pipeline.handle );
    m_shaderPipelines.erase( _pipeline );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bindPipeline( ShaderPipelineID _pipeline )
{
    //m_currentlyBoundPipeline = _pipeline;
    ShaderPipeline& pipeline = m_shaderPipelines.at( _pipeline );
    glBindProgramPipeline( pipeline.handle );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bindVertexLayout( VertexLayout* _pVertexLayout )
{
    int pointer = 0;
    for( size_t i = 0; i < _pVertexLayout->numAttributes; i++ )
    {
        VertexAttrib* attrib = &_pVertexLayout->attributes[ i ];

        GLenum type = GL_NONE;
        switch( attrib->type )
        {
        case afx::Type::kFLOAT:        type = GL_FLOAT;        break;
        case afx::Type::kINT:          type = GL_INT;          break;
        case afx::Type::kUNSIGNED_INT: type = GL_UNSIGNED_INT; break;
        }

        glVertexAttribPointer( i, attrib->componentCount, type, attrib->normalized, _pVertexLayout->stride, (const void*)pointer );
        glEnableVertexAttribArray( i );

        pointer += attrib->size;
    }

    return ARG_SUCESS;
}

Result OpenGLRenderer::createBuffer( BufferDesc* _desc, BufferID* _pBuffer )
{
    Buffer buffer{};
    buffer.type = _desc->type;
    buffer.usage = _desc->usage;
    buffer.size = _desc->size;

    GLenum usage = getGlBufferUsage( buffer.usage );

    glCreateBuffers( 1, &buffer.handle );
    glNamedBufferData( buffer.handle, _desc->size, 0, usage );

    *_pBuffer = m_buffers.emplace( buffer );
    if( *_pBuffer == 0 )
        return ARG_ERROR_OUT_OF_MEMORY;

    return ARG_SUCESS;
}

Result OpenGLRenderer::destroyBuffer( BufferID _buffer )
{
    Buffer& buffer = m_buffers.at( _buffer );
    glDeleteBuffers( 1, &buffer.handle );
    m_buffers.erase( _buffer );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bindBuffer( BufferID _buffer )
{
    Buffer& buffer = m_buffers.at( _buffer );
    GLenum target = getGlBufferEnum( buffer.type );
    glBindBuffer( target, buffer.handle );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bindBufferIndex( BufferID _buffer, int32_t _bindingIndex )
{
    Buffer& buffer = m_buffers.at( _buffer );
    GLenum target = getGlBufferEnum( buffer.type );
    glBindBufferBase( target, _bindingIndex, buffer.handle );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bufferData( BufferID _buffer, void* _pData, size_t _size )
{
    Buffer& buffer = m_buffers.at( _buffer );
    GLenum usage = getGlBufferUsage( buffer.usage );
    glNamedBufferData( buffer.handle, _size, _pData, usage );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base )
{
    Buffer& buffer = m_buffers.at( _buffer );
    glNamedBufferSubData( buffer.handle, _base, _size, _pData );

    return ARG_SUCESS;
}

Result OpenGLRenderer::copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
    Buffer& readBuffer = m_buffers.at( _readBuffer );
    Buffer& writeBuffer = m_buffers.at( _writeBuffer );
    
    glCopyNamedBufferSubData( readBuffer.handle, writeBuffer.handle, _readOffset, _writeOffset, _size );

    return ARG_SUCESS;
}

Result OpenGLRenderer::bindVertexBuffer( BufferID _vertexPullBuffer )
{
    Buffer& buffer = m_buffers.at( _vertexPullBuffer );
    printf( "argGfxBindVertexBuffer is not implemented\n" );

    // bindBufferIndex( m_vertexBuffer, SbVertices.bindingIndex.value );
    // bindBuffer( m_indexBuffer );

    return ARG_SUCESS;
}

void OpenGLRenderer::_cmdBegin( const CmdBuffer& _cmd )
{
}

void OpenGLRenderer::_cmdEnd( const CmdBuffer& _cmd )
{
}

void OpenGLRenderer::_cmdSubmit( const CmdBuffer& _cmd )
{
}

void OpenGLRenderer::_cmdBeginRender( const CmdBuffer& _rCmd, Image& _rImage )
{
}

void OpenGLRenderer::_cmdEndRender( const CmdBuffer& _rCmd )
{
}

void OpenGLRenderer::_cmdImageClear( const CmdBuffer& _cmd, const Image& _rImage, float _r, float _g, float _b, float _a )
{
}

void OpenGLRenderer::_cmdImageBlit( const CmdBuffer& _rCmd, const Image& _rSrc, const Image& _rDst )
{
}

void OpenGLRenderer::_cmdBindPipeline( const CmdBuffer& _rCmd, const ShaderPipeline& _rShader )
{
}

void OpenGLRenderer::_cmdDispatch( const CmdBuffer& _rCmd, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ )
{
}

void OpenGLRenderer::_cmdViewport( const CmdBuffer& _rCmd, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height )
{
}

void OpenGLRenderer::_cmdDraw( const CmdBuffer& _rCmd, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance )
{
}

void OpenGLRenderer::_cmdDrawIndexed( const CmdBuffer& _rCmd, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance )
{
}

void OpenGLRenderer::_cmdCopyBuffer( const CmdBuffer& _rCmd, const Buffer& _rSrc, const Buffer& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size )
{
}

void OpenGLRenderer::_cmdBindIndexBuffer( const CmdBuffer& _rCmd, const Buffer& _rIndexBuffer, size_t _offset, Type _type )
{
}

}