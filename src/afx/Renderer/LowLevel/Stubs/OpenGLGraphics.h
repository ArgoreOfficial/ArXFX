#pragma once

#include <afx/Renderer/LowLevel/LowLevelGraphics.h>

namespace afx { 

class OpenGLGraphics : public ILowLevelGraphics
{
public:
	// Inherited via ILowLevelRenderer
	Result init() override;
	Result viewport( int _x, int _y, int _width, int _height ) override;
	void clearColor( float _r, float _g, float _b, float _a ) override;
	void clearDepth( float _r, float _g, float _b, float _a ) override;
	Result setFillMode( FillMode _mode ) override;
	Result draw( uint32_t _firstVertex, uint32_t _numVertices ) override;
	Result drawIndexed( uint32_t _numIndices ) override;
	Result drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex ) override;
	Result createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram ) override;
	Result destroyProgram( ShaderModuleID _program ) override;
	Result createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline ) override;
	Result destroyPipeline( ShaderPipelineID _pipeline ) override;
	Result bindPipeline( ShaderPipelineID _pipeline ) override;
	Result bindVertexLayout( VertexLayout* _pVertexLayout ) override;
	Result createBuffer( BufferDesc* _desc, BufferID* _pBuffer ) override;
	Result destroyBuffer( BufferID _buffer ) override;
	Result bindBuffer( BufferID _buffer ) override;
	Result bindBufferIndex( BufferID _buffer, int32_t _bindingIndex ) override;
	Result bufferData( BufferID _buffer, void* _pData, size_t _size ) override;
	Result bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base ) override;
	Result copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size ) override;
	Result bindVertexBuffer( BufferID _vertexPullBuffer ) override;

private:
	void _cmdBegin( const CmdBuffer& _cmd ) override;
	void _cmdEnd( const CmdBuffer& _cmd ) override;
	void _cmdSubmit( const CmdBuffer& _cmd ) override;
	void _cmdBeginRender( const CmdBuffer& _rCmd, Image& _rImage ) override;
	void _cmdEndRender( const CmdBuffer& _rCmd ) override;
	void _cmdImageClear( const CmdBuffer& _cmd, const Image& _rImage, float _r, float _g, float _b, float _a ) override;
	void _cmdImageBlit( const CmdBuffer& _rCmd, const Image& _rSrc, const Image& _rDst ) override;
	void _cmdBindPipeline( const CmdBuffer& _rCmd, const ShaderPipeline& _rShader ) override;
	void _cmdDispatch( const CmdBuffer& _rCmd, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ ) override;
	void _cmdViewport( const CmdBuffer& _rCmd, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height ) override;
	void _cmdDraw( const CmdBuffer& _rCmd, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance ) override;
	void _cmdDrawIndexed( const CmdBuffer& _rCmd, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance ) override;
	void _cmdCopyBuffer( const CmdBuffer& _rCmd, const Buffer& _rSrc, const Buffer& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size ) override;
	void _cmdBindIndexBuffer( const CmdBuffer& _rCmd, const Buffer& _rIndexBuffer, size_t _offset, Type _type ) override;

	static ILowLevelGraphics::Entry g_register;
};

}
