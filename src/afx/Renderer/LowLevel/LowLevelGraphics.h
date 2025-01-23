#pragma once

#include <arx/registry.hpp>
#include <arx/strong_type.hpp>
#include <arx/unordered_array.hpp>

#include <afx/Math/Bounds2D.h>

#include <afx/Renderer/Buffer.h>
#include <afx/Renderer/CmdBuffer.h>
#include <afx/Renderer/Image.h>
#include <afx/Renderer/ShaderPipeline.h>

#include <unordered_map>
#include <string>

namespace afx
{

class ILowLevelGraphics : public arx::registry<ILowLevelGraphics>
{
public:
	virtual Result init() = 0;
	virtual void viewport( int _x, int _y, int _width, int _height ) = 0;
	virtual void clearColor( float _r, float _g, float _b, float _a ) = 0;
	virtual void clearDepth( float _r, float _g, float _b, float _a ) = 0;
	virtual void setFillMode( FillMode _mode ) = 0;
	virtual void draw( uint32_t _firstVertex, uint32_t _numVertices ) = 0;
	virtual void drawIndexed( uint32_t _numIndices ) = 0;
	virtual void drawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex ) = 0;
	virtual void createProgram( ShaderProgramDesc* _desc, ShaderModuleID* _pProgram ) = 0;
	virtual void destroyProgram( ShaderModuleID _program ) = 0;
	virtual void createPipeline( ShaderPipelineDesc* _desc, ShaderPipelineID* _pPipeline ) = 0;
	virtual void destroyPipeline( ShaderPipelineID _pipeline ) = 0;
	virtual void bindPipeline( ShaderPipelineID _pipeline ) = 0;
	virtual void bindVertexLayout( VertexLayout* _pVertexLayout ) = 0;
	virtual void createBuffer( BufferDesc* _desc, BufferID* _pBuffer ) = 0;
	virtual void destroyBuffer( BufferID _buffer ) = 0;
	virtual void bindBuffer( BufferID _buffer ) = 0;
	virtual void bindBufferIndex( BufferID _buffer, int32_t _bindingIndex ) = 0;
	virtual void bufferData( BufferID _buffer, void* _pData, size_t _size ) = 0;
	virtual void bufferSubData( BufferID _buffer, void* _pData, size_t _size, size_t _base ) = 0;
	virtual void copyBufferSubData( BufferID _readBuffer, BufferID _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size ) = 0;
	virtual void bindVertexBuffer( BufferID _vertexPullBuffer ) = 0;

	virtual CmdBuffer* createCmdBuffer() = 0;

	inline void cmdBegin( CmdBufferID _cmdID ) {
		_cmdBegin( m_cmdBuffers.at( _cmdID ) );
	}

	inline void cmdEnd( CmdBufferID _cmdID ) {
		_cmdEnd( m_cmdBuffers.at( _cmdID ) );
	}

	inline void cmdSubmit( CmdBufferID _cmdID ) {
		_cmdSubmit( m_cmdBuffers.at( _cmdID ) );
	}

	inline void cmdBeginRender( CmdBufferID _cmdID, ImageID _imageID ) {
		_cmdBeginRender( m_cmdBuffers[ _cmdID ], m_images[ _imageID ] );
	}

	inline void cmdEndRender( CmdBufferID _cmdID ) {
		_cmdEndRender( m_cmdBuffers[ _cmdID ] );
	}

	inline void cmdImageClear( CmdBufferID _cmdID, ImageID _imageID, float _r, float _g, float _b, float _a ) {
		_cmdImageClear( m_cmdBuffers[ _cmdID ], m_images[ _imageID ], _r, _g, _b, _a );
	}

	inline void cmdImageBlit( CmdBufferID _cmdID, ImageID _srcID, ImageID  _dstID ) {
		_cmdImageBlit( m_cmdBuffers[ _cmdID ], m_images[ _srcID ], m_images[ _dstID ] );
	}

	inline void cmdBindPipeline( CmdBufferID _cmdID, ShaderPipelineID _pipelineID ) {
		_cmdBindPipeline( m_cmdBuffers[ _cmdID ], m_shaderPipelines[ _pipelineID ] );
	}

	inline void cmdDispatch( CmdBufferID _cmdID, uint32_t _numGroupsX, uint32_t _numGroupsY, uint32_t _numGroupsZ ) {
		_cmdDispatch( m_cmdBuffers[ _cmdID ], _numGroupsX, _numGroupsY, _numGroupsZ );
	}

	inline void cmdViewport( CmdBufferID _cmdID, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height ) {
		_cmdViewport( m_cmdBuffers[ _cmdID ], _x, _y, _width, _height );
	}

	inline void cmdViewport( CmdBufferID _cmdID, Bounds2Di _viewport ) {
		_cmdViewport( m_cmdBuffers[ _cmdID ], _viewport.x, _viewport.y, _viewport.width, _viewport.height );
	}

	inline void cmdDraw( CmdBufferID _cmdID, uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance ) {
		_cmdDraw( m_cmdBuffers[ _cmdID ], _vertexCount, _instanceCount, _firstVertex, _firstInstance );
	}

	inline void cmdDrawIndexed( CmdBufferID _cmdID, uint32_t _indexCount, uint32_t _instanceCount, uint32_t _firstIndex, int32_t _vertexOffset, uint32_t _firstInstance ) {
		_cmdDrawIndexed( m_cmdBuffers[ _cmdID ], _indexCount, _instanceCount, _firstIndex, _vertexOffset, _firstInstance );
	}

	inline void cmdCopyBuffer( CmdBufferID _cmdID, BufferID _srcID, BufferID _dstID, size_t _srcOffset, size_t _dstOffset, size_t _size ) {
		_cmdCopyBuffer( m_cmdBuffers[ _cmdID ], m_buffers[ _srcID ], m_buffers[ _dstID ], _srcOffset, _dstOffset, _size );
	}

	inline void cmdBindIndexBuffer( CmdBufferID _cmdID, BufferID _indexBufferID, size_t _offset, Type _type ) {
		_cmdBindIndexBuffer( m_cmdBuffers[ _cmdID ], m_buffers[ _indexBufferID ], _offset, _type );
	}

public:

	virtual void _cmdBegin( 
		CmdBuffer& _cmd ) = 0;
	
	virtual void _cmdEnd( 
		CmdBuffer& _cmd ) = 0;
	
	virtual void _cmdSubmit( 
		CmdBuffer& _cmd ) = 0;
	
	virtual void _cmdBeginRender( 
		CmdBuffer& _rCmd, 
		Image& _rImage ) = 0;
	
	virtual void _cmdEndRender( 
		CmdBuffer& _rCmd ) = 0;
	
	virtual void _cmdImageClear( 
		CmdBuffer& _cmd, 
		Image& _rImage, 
		float _r, 
		float _g, 
		float _b, 
		float _a ) = 0;
	
	virtual void _cmdImageBlit( 
		CmdBuffer& _rCmd, 
		Image& _rSrc, 
		Image& _rDst ) = 0;
	
	virtual void _cmdBindPipeline( 
		CmdBuffer& _rCmd, 
		ShaderPipeline& _rShader ) = 0;
	
	virtual void _cmdDispatch( 
		CmdBuffer& _rCmd, 
		uint32_t _numGroupsX, 
		uint32_t _numGroupsY, 
		uint32_t _numGroupsZ ) = 0;
	
	virtual void _cmdViewport( 
		CmdBuffer& _rCmd, 
		uint32_t _x, 
		uint32_t _y, 
		uint32_t _width, 
		uint32_t _height ) = 0;
	
	virtual void _cmdDraw( 
		CmdBuffer& _rCmd, 
		uint32_t _vertexCount, 
		uint32_t _instanceCount, 
		uint32_t _firstVertex, 
		uint32_t _firstInstance ) = 0;
	
	virtual void _cmdDrawIndexed( 
		CmdBuffer& _rCmd, 
		uint32_t _indexCount, 
		uint32_t _instanceCount, 
		uint32_t _firstIndex, 
		int32_t _vertexOffset, 
		uint32_t _firstInstance ) = 0;
	
	virtual void _cmdCopyBuffer( 
		CmdBuffer& _rCmd, 
		Buffer& _rSrc, 
		Buffer& _rDst, 
		size_t _srcOffset, 
		size_t _dstOffset, 
		size_t _size ) = 0;

	virtual void _cmdBindIndexBuffer( 
		CmdBuffer& _rCmd, 
		Buffer& _rIndexBuffer, 
		size_t _offset, 
		Type _type ) = 0;

protected:
	bool m_shouldRender{ true };

	arx::unordered_array<CmdBufferID,      CmdBuffer>        m_cmdBuffers;
	arx::unordered_array<ImageID,          Image>            m_images;
	arx::unordered_array<ShaderModuleID,   ShaderModule>     m_shaderModules;
	arx::unordered_array<ShaderPipelineID, ShaderPipeline>   m_shaderPipelines;
	arx::unordered_array<BufferID,         Buffer>           m_buffers;
	
	CmdBufferID m_currentCmdBuffer{};


};

}