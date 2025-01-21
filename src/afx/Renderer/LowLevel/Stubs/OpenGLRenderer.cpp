#include "OpenGLRenderer.h"

namespace afx {


ILowLevelRenderer* openGLRendererAllocator( void* _pUserData ) {
    return new OpenGLRenderer();
}

ILowLevelRenderer::Entry OpenGLRenderer::g_register{ "OpenGL", openGLRendererAllocator };

Result OpenGLRenderer::init()
{
    return Result();
}

Result OpenGLRenderer::viewport( int _x, int _y, int _width, int _height )
{
    return Result();
}

Result OpenGLRenderer::setClearColor( float _r, float _g, float _b, float _a )
{
    return Result();
}

Result OpenGLRenderer::clearRenderTarget( ClearMask _mask )
{
    return Result();
}

Result OpenGLRenderer::setFillMode( FillMode _mode )
{
    return Result();
}

Result OpenGLRenderer::draw( uint32_t _firstVertex, uint32_t _numVertices )
{
    return Result();
}

Result OpenGLRenderer::drawIndexed( uint32_t _numIndices )
{
    return Result();
}

Result OpenGLRenderer::drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
    return Result();
}

Result OpenGLRenderer::createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram )
{
    return Result();
}

Result OpenGLRenderer::destroyProgram( ShaderModuleID _program )
{
    return Result();
}

Result OpenGLRenderer::createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline )
{
    return Result();
}

Result OpenGLRenderer::destroyPipeline( ShaderPipelineID _pipeline )
{
    return Result();
}

Result OpenGLRenderer::bindPipeline( ShaderPipelineID _pipeline )
{
    return Result();
}

Result OpenGLRenderer::bindVertexLayout( VertexLayout* _pVertexLayout )
{
    return Result();
}

Result OpenGLRenderer::createBuffer( BufferDesc* _desc, BufferID* _pBuffer )
{
    return Result();
}

Result OpenGLRenderer::destroyBuffer( BufferID _buffer )
{
    return Result();
}

Result OpenGLRenderer::bindBuffer( BufferID _buffer )
{
    return Result();
}

Result OpenGLRenderer::bindBufferIndex( BufferID _buffer, int32_t _bindingIndex )
{
    return Result();
}

Result OpenGLRenderer::bufferData( BufferID _buffer, void* _pData, size_t _size )
{
    return Result();
}

Result OpenGLRenderer::bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base )
{
    return Result();
}

Result OpenGLRenderer::copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
    return Result();
}

Result OpenGLRenderer::bindVertexBuffer( BufferID _vertexPullBuffer )
{
    return Result();
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

void OpenGLRenderer::_cmdCopyBuffer( const CmdBuffer& _rCmd, const BufferID& _rSrc, const BufferID& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size )
{
}

void OpenGLRenderer::_cmdBindIndexBuffer( const CmdBuffer& _rCmd, const BufferID& _rIndexBuffer, size_t _offset, Type _type )
{
}

}