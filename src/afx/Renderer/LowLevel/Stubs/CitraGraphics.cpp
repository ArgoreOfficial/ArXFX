#ifdef AFX_ARCH_CITRA

#include "CitraGraphics.h"

#include <3ds.h>
#include <citro3d.h>

afx::Result afx::CitraGraphics::init()
{
	// Initialize graphics
	gfxInitDefault();
	C3D_Init( C3D_DEFAULT_CMDBUF_SIZE );

    return Result::kSUCESS;
}

void afx::CitraGraphics::viewport( int _x, int _y, int _width, int _height )
{
}

void afx::CitraGraphics::clearColor( float _r, float _g, float _b, float _a )
{
}

void afx::CitraGraphics::clearDepth( float _r, float _g, float _b, float _a )
{
}

void afx::CitraGraphics::setFillMode( FillMode _mode )
{
}

void afx::CitraGraphics::draw( uint32_t _firstVertex, uint32_t _numVertices )
{
}

void afx::CitraGraphics::drawIndexed( uint32_t _numIndices )
{
}

void afx::CitraGraphics::drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
}

void afx::CitraGraphics::createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram )
{
}

void afx::CitraGraphics::destroyProgram( ShaderModuleID _program )
{
}

void afx::CitraGraphics::createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline )
{
}

void afx::CitraGraphics::destroyPipeline( ShaderPipelineID _pipeline )
{
}

void afx::CitraGraphics::bindPipeline( ShaderPipelineID _pipeline )
{
}

void afx::CitraGraphics::bindVertexLayout( VertexLayout* _pVertexLayout )
{
}

afx::BufferID afx::CitraGraphics::createBuffer( BufferType _type, BufferUsage _usage, int32_t _size )
{
    return BufferID();
}

void afx::CitraGraphics::destroyBuffer( BufferID _buffer )
{
}

void afx::CitraGraphics::bindBuffer( BufferID _buffer )
{
}

void afx::CitraGraphics::bindBufferIndex( BufferID _buffer, int32_t _bindingIndex )
{
}

void afx::CitraGraphics::bufferData( BufferID _buffer, void* _pData, size_t _size )
{
}

void afx::CitraGraphics::bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base )
{
}

void afx::CitraGraphics::copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
}

void afx::CitraGraphics::bindVertexBuffer( BufferID _vertexPullBuffer )
{
}

afx::CmdBuffer* afx::CitraGraphics::createCmdBuffer()
{
	return nullptr;
}

void afx::CitraGraphics::_cmdBegin( CmdBuffer& _cmd )
{
}

void afx::CitraGraphics::_cmdEnd( CmdBuffer& _cmd )
{
}

void afx::CitraGraphics::_cmdSubmit( CmdBuffer& _cmd )
{
}

void afx::CitraGraphics::_cmdBeginRender( CmdBuffer& _rCmd, Image& _rImage )
{
}

void afx::CitraGraphics::_cmdEndRender( CmdBuffer& _rCmd )
{
}

void afx::CitraGraphics::_cmdImageClear( CmdBuffer& _cmd, Image& _rImage, float _r, float _g, float _b, float _a )
{
}

void afx::CitraGraphics::_cmdImageBlit( CmdBuffer& _rCmd, Image& _rSrc, Image& _rDst )
{
}

void afx::CitraGraphics::_cmdBindPipeline( CmdBuffer& _rCmd, ShaderPipeline& _rShader )
{
}

void afx::CitraGraphics::_cmdDispatch( CmdBuffer& _rCmd, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ )
{
}

void afx::CitraGraphics::_cmdViewport( CmdBuffer& _rCmd, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height )
{
}

void afx::CitraGraphics::_cmdDraw( CmdBuffer& _rCmd, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance )
{
}

void afx::CitraGraphics::_cmdDrawIndexed( CmdBuffer& _rCmd, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance )
{
}

void afx::CitraGraphics::_cmdCopyBuffer( CmdBuffer& _rCmd, Buffer& _rSrc, Buffer& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size )
{
}

void afx::CitraGraphics::_cmdBindIndexBuffer( CmdBuffer& _rCmd, Buffer& _rIndexBuffer, size_t _offset, Type _type )
{
}

#endif