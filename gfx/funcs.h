#pragma once

#include <stdint.h>
#include "gfx_types.h"

//
void Viewport( int _x, int _y, int _width, int _height );

RenderTargetID CreateRenderTarget( RenderTargetID _renderTargetID, sRenderTargetDesc* _desc );
void DestroyRenderTarget( RenderTargetID _renderTargetID );
void SetRenderTarget( RenderTargetID _renderTargetID );

void SetClearColor( float _r, float _g, float _b, float _a );
void ClearRenderTarget( GfxClearMask _mask );

ProgramID CreateProgram( ProgramID _programID, sProgramDesc* _desc );
void DestroyProgram( ProgramID _programID );

PipelineID CreatePipeline( PipelineID _pipelineID, sPipelineDesc* _desc );
void DestroyPipeline( PipelineID _pipelineID );
void BindPipeline( PipelineID _pipelineID );

GPUBufferID CreateGPUBuffer( GPUBufferID _bufferID, sGPUBufferDesc* _desc );
void DestroyGPUBuffer( GPUBufferID _bufferID );
		
void BindBuffer( GPUBufferID _bufferID );
void BindBufferIndex( GPUBufferID _bufferID, int32_t _bindingIndex );

void BufferData( GPUBufferID _bufferID, void* _pData, size_t _size );
void BufferSubData( GPUBufferID _bufferID, void* _pData, size_t _size, size_t _base );

void CopyBufferSubData( GPUBufferID _readBufferID, GPUBufferID _writeBufferID, size_t _readOffset, size_t _writeOffset, size_t _size );

TextureID CreateTexture( TextureID _textureID, sTextureDesc* _pDesc );
void BufferTextureData( TextureID _textureID, void* _pData, int _generateMipMaps );
void DestroyTexture( TextureID _textureID );
void BindTextureToSlot( TextureID _textureID, unsigned int _slot );

void BindVertexBuffer( GPUBufferID _vertexPullBufferID );

void SetFillMode( GfxFillMode _mode );

void Draw( uint32_t _firstVertex, uint32_t _numVertices );
void DrawIndexed( uint32_t _numIndices );
void DrawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
void DrawMultiIndirect( DrawListID _drawListID );