#pragma once

#include <stdint.h>
#include "gfx_types.h"

//
void Viewport( int _x, int _y, int _width, int _height );

GfxRenderTargetID CreateRenderTarget( GfxRenderTargetID _renderTargetID, sGfxRenderTargetDesc* _desc );
void DestroyRenderTarget( GfxRenderTargetID _renderTargetID );
void SetRenderTarget( GfxRenderTargetID _renderTargetID );

void SetClearColor( float _r, float _g, float _b, float _a );
void ClearRenderTarget( GfxClearMask _mask );

GfxProgramID CreateProgram( GfxProgramID _programID, sGfxProgramDesc* _desc );
void DestroyProgram( GfxProgramID _programID );

GfxPipelineID CreatePipeline( GfxPipelineID _pipelineID, sGfxPipelineDesc* _desc );
void DestroyPipeline( GfxPipelineID _pipelineID );
void BindPipeline( GfxPipelineID _pipelineID );

GfxGPUBufferID CreateGPUBuffer( GfxGPUBufferID _bufferID, sGfxGPUBufferDesc* _desc );
void DestroyGPUBuffer( GfxGPUBufferID _bufferID );
		
void BindBuffer( GfxGPUBufferID _bufferID );
void BindBufferIndex( GfxGPUBufferID _bufferID, int32_t _bindingIndex );

void BufferData( GfxGPUBufferID _bufferID, void* _pData, size_t _size );
void BufferSubData( GfxGPUBufferID _bufferID, void* _pData, size_t _size, size_t _base );

void CopyBufferSubData( GfxGPUBufferID _readBufferID, GfxGPUBufferID _writeBufferID, size_t _readOffset, size_t _writeOffset, size_t _size );

GfxTextureID CreateTexture( GfxTextureID _textureID, sGfxTextureDesc* _pDesc );
void BufferTextureData( GfxTextureID _textureID, void* _pData, int _generateMipMaps );
void DestroyTexture( GfxTextureID _textureID );
void BindTextureToSlot( GfxTextureID _textureID, unsigned int _slot );

void BindVertexBuffer( GfxGPUBufferID _vertexPullBufferID );

void SetFillMode( GfxFillMode _mode );

void Draw( uint32_t _firstVertex, uint32_t _numVertices );
void DrawIndexed( uint32_t _numIndices );
void DrawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
void DrawMultiIndirect( GfxDrawListID _drawListID );