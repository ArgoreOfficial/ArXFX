#pragma once

#include <arg/gfx.h>

namespace arx
{

class ILowLevelRenderer
{
public:
	ArgResult argGfxInit();

	ArgResult argGfxCreateContext(
		ArgGfxContext* _pContext );

	ArgResult viewport(
		ArgGfxContext _ctx,
		int _x,
		int _y,
		int _width,
		int _height );

	ArgResult setClearColor(
		ArgGfxContext _ctx,
		float _r,
		float _g,
		float _b,
		float _a );

	ArgResult clearRenderTarget(
		ArgGfxContext _ctx,
		ArgGfxClearMask _mask );

	ArgResult setFillMode(
		ArgGfxContext _ctx,
		ArgGfxFillMode _mode );

	ArgResult Draw(
		ArgGfxContext _ctx,
		uint32_t _firstVertex,
		uint32_t _numVertices );

	ArgResult DrawIndexed(
		ArgGfxContext _ctx,
		uint32_t _numIndices );

	ArgResult DrawIndexedInstanced(
		ArgGfxContext _ctx,
		uint32_t _numIndices,
		uint32_t _numInstances,
		uint32_t _baseVertex );

	ArgResult CreateProgram(
		ArgGfxContext _ctx,
		ArgGfxProgramDesc* _desc,
		ArgGfxProgram* _pProgram );

	ArgResult DestroyProgram(
		ArgGfxContext _ctx,
		ArgGfxProgram _program );

	ArgResult CreatePipeline(
		ArgGfxContext _ctx,
		ArgGfxPipelineDesc* _desc,
		ArgGfxPipeline* _pPipeline );

	ArgResult DestroyPipeline(
		ArgGfxContext _ctx,
		ArgGfxPipeline _pipeline );

	ArgResult BindPipeline(
		ArgGfxContext _ctx,
		ArgGfxPipeline _pipeline );

	ArgResult BindVertexLayout(
		ArgGfxContext _ctx,
		ArgGfxVertexLayout* _pVertexLayout );

	ArgResult CreateBuffer(
		ArgGfxContext _ctx,
		ArgGfxBufferDesc* _desc,
		ArgGfxBuffer* _pBuffer );

	ArgResult DestroyBuffer(
		ArgGfxContext _ctx,
		ArgGfxBuffer _buffer );

	ArgResult BindBuffer(
		ArgGfxContext _ctx,
		ArgGfxBuffer _buffer );

	ArgResult BindBufferIndex(
		ArgGfxContext _ctx,
		ArgGfxBuffer _buffer,
		int32_t _bindingIndex );

	ArgResult BufferData(
		ArgGfxContext _ctx,
		ArgGfxBuffer _buffer,
		void* _pData,
		size_t _size );

	ArgResult BufferSubData(
		ArgGfxContext _ctx,
		ArgGfxBuffer _buffer,
		void* _pData,
		size_t _size,
		size_t _base );

	ArgResult CopyBufferSubData(
		ArgGfxContext _ctx,
		ArgGfxBuffer _readBuffer,
		ArgGfxBuffer _writeBuffer,
		size_t _readOffset,
		size_t _writeOffset,
		size_t _size );

	ArgResult BindVertexBuffer(
		ArgGfxContext _ctx,
		ArgGfxBuffer _vertexPullBuffer );


};

}