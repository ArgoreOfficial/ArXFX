#ifdef ARC_PLATFORM_3DS

#include "CitraGraphics.h"

#include <3ds.h>
#include <citro3d.h>

arc::Result arc::CitraGraphics::init()
{
	// Initialize graphics
	gfxInitDefault();
	C3D_Init( C3D_DEFAULT_CMDBUF_SIZE );

	consoleInit( GFX_BOTTOM, 0 );

    return Result::kSUCESS;
}

void arc::CitraGraphics::viewport( int _x, int _y, int _width, int _height )
{
}

void arc::CitraGraphics::clearColor( float _r, float _g, float _b, float _a )
{
}

void arc::CitraGraphics::clearDepth( float _r, float _g, float _b, float _a )
{
}

void arc::CitraGraphics::setFillMode( FillMode _mode )
{
}

void arc::CitraGraphics::draw( uint32_t _firstVertex, uint32_t _numVertices )
{
}

void arc::CitraGraphics::drawIndexed( uint32_t _numIndices )
{
}

void arc::CitraGraphics::drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex )
{
}

void arc::CitraGraphics::createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram )
{
}

void arc::CitraGraphics::destroyProgram( ShaderModuleID _program )
{
}

void arc::CitraGraphics::createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline )
{
}

void arc::CitraGraphics::destroyPipeline( ShaderPipelineID _pipeline )
{
}

void arc::CitraGraphics::bindPipeline( ShaderPipelineID _pipeline )
{
}

void arc::CitraGraphics::bindVertexLayout( VertexLayout* _pVertexLayout )
{
}

arc::BufferID arc::CitraGraphics::createBuffer( BufferType _type, BufferUsage _usage, int32_t _size )
{
    return BufferID();
}

void arc::CitraGraphics::destroyBuffer( BufferID _buffer )
{
}

void arc::CitraGraphics::bindBuffer( BufferID _buffer )
{
}

void arc::CitraGraphics::bindBufferIndex( BufferID _buffer, int32_t _bindingIndex )
{
}

void arc::CitraGraphics::bufferData( BufferID _buffer, void* _pData, size_t _size )
{
}

void arc::CitraGraphics::bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base )
{
}

void arc::CitraGraphics::copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size )
{
}

void arc::CitraGraphics::bindVertexBuffer( BufferID _vertexPullBuffer )
{
}

arc::CmdBuffer* arc::CitraGraphics::createCmdBuffer()
{
	return nullptr;
}

void arc::CitraGraphics::_cmdBegin( CmdBuffer& _cmd )
{
}

void arc::CitraGraphics::_cmdEnd( CmdBuffer& _cmd )
{
}

void arc::CitraGraphics::_cmdSubmit( CmdBuffer& _cmd )
{
}

void arc::CitraGraphics::_cmdBeginRender( CmdBuffer& _rCmd, Image& _rImage )
{
}

void arc::CitraGraphics::_cmdEndRender( CmdBuffer& _rCmd )
{
}

void arc::CitraGraphics::_cmdImageClear( CmdBuffer& _cmd, Image& _rImage, float _r, float _g, float _b, float _a )
{
}

void arc::CitraGraphics::_cmdImageBlit( CmdBuffer& _rCmd, Image& _rSrc, Image& _rDst )
{
}

void arc::CitraGraphics::_cmdBindPipeline( CmdBuffer& _rCmd, ShaderPipeline& _rShader )
{
}

void arc::CitraGraphics::_cmdDispatch( CmdBuffer& _rCmd, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ )
{
}

void arc::CitraGraphics::_cmdViewport( CmdBuffer& _rCmd, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height )
{
}

void arc::CitraGraphics::_cmdDraw( CmdBuffer& _rCmd, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance )
{
}

void arc::CitraGraphics::_cmdDrawIndexed( CmdBuffer& _rCmd, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance )
{
}

void arc::CitraGraphics::_cmdCopyBuffer( CmdBuffer& _rCmd, Buffer& _rSrc, Buffer& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size )
{
}

void arc::CitraGraphics::_cmdBindIndexBuffer( CmdBuffer& _rCmd, Buffer& _rIndexBuffer, size_t _offset, Type _type )
{
}

#endif