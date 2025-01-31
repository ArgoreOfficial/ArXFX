#pragma once

#ifdef ARC_SUPPORT_OPENGL

#include <afx/Renderer/LowLevel/LowLevelGraphics.h>
#include <arx/registry.hpp>

namespace arc { 

// TODO: move
struct col
{
	float r, g, b, a;
};

class OpenGLGraphics : public arx::registar<OpenGLGraphics, ILowLevelGraphics>
{
public:
	static std::string get_name() { return "OpenGL"; }
	static ILowLevelGraphics* alloc( void* _pUserData ) { return new OpenGLGraphics(); }

	// Inherited via ILowLevelRenderer
	Result init() override;
	void viewport( int _x, int _y, int _width, int _height ) override;
	void clearColor( float _r, float _g, float _b, float _a ) override;
	void clearDepth( float _r, float _g, float _b, float _a ) override;
	void setFillMode( FillMode _mode ) override;
	void draw( uint32_t _firstVertex, uint32_t _numVertices ) override;
	void drawIndexed( uint32_t _numIndices ) override;
	void drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex ) override;
	void createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram ) override;
	void destroyProgram( ShaderModuleID _program ) override;
	void createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline ) override;
	void destroyPipeline( ShaderPipelineID _pipeline ) override;
	void bindPipeline( ShaderPipelineID _pipeline ) override;
	void bindVertexLayout( VertexLayout* _pVertexLayout ) override;
	BufferID createBuffer( BufferType _type, BufferUsage _usage, int32_t _size ) override;
	void destroyBuffer( BufferID _buffer ) override;
	void bindBuffer( BufferID _buffer ) override;
	void bindBufferIndex( BufferID _buffer, int32_t _bindingIndex ) override;
	void bufferData( BufferID _buffer, void* _pData, size_t _size ) override;
	void bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base ) override;
	void copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size ) override;
	void bindVertexBuffer( BufferID _vertexPullBuffer ) override;

	CmdBuffer* createCmdBuffer() override;

	void _cmdBegin( CmdBuffer& _cmd ) override;
	void _cmdEnd( CmdBuffer& _cmd ) override;
	void _cmdSubmit( CmdBuffer& _cmd ) override;
	void _cmdBeginRender( CmdBuffer& _rCmd, Image& _rImage ) override;
	void _cmdEndRender( CmdBuffer& _rCmd ) override;
	void _cmdImageClear( CmdBuffer& _cmd, Image& _rImage, float _r, float _g, float _b, float _a ) override;
	void _cmdImageBlit( CmdBuffer& _rCmd, Image& _rSrc, Image& _rDst ) override;
	void _cmdBindPipeline( CmdBuffer& _rCmd, ShaderPipeline& _rShader ) override;
	void _cmdDispatch( CmdBuffer& _rCmd, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ ) override;
	void _cmdViewport( CmdBuffer& _rCmd, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height ) override;
	void _cmdDraw( CmdBuffer& _rCmd, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance ) override;
	void _cmdDrawIndexed( CmdBuffer& _rCmd, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance ) override;
	void _cmdCopyBuffer( CmdBuffer& _rCmd, Buffer& _rSrc, Buffer& _rDst, size_t _srcOffset, size_t _dstOffset, size_t _size ) override;
	void _cmdBindIndexBuffer( CmdBuffer& _rCmd, Buffer& _rIndexBuffer, size_t _offset, Type _type ) override;

private:
	unsigned int m_VAO{ 0 }; // opengl workaround

};

}

#endif