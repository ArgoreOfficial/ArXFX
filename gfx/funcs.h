#pragma once

#include <stdint.h>
#include "gfx_types.h"

//
void gfxViewport( int _x, int _y, int _width, int _height );

GfxRenderTarget gfxCreateRenderTarget( GfxRenderTarget _renderTarget, GfxRenderTargetDesc* _desc );
void gfxDestroyRenderTarget( GfxRenderTarget _renderTarget );
void gfxSetRenderTarget( GfxRenderTarget _renderTarget );

void gfxSetClearColor( float _r, float _g, float _b, float _a );
void gfxClearRenderTarget( GfxClearMask _mask );

GfxProgram gfxCreateProgram( GfxProgram _program, GfxProgramDesc* _desc );
void gfxDestroyProgram( GfxProgram _program );

GfxPipeline gfxCreatePipeline( GfxPipeline _pipeline, GfxPipelineDesc* _desc );
void gfxDestroyPipeline( GfxPipeline _pipeline );
void gfxBindPipeline( GfxPipeline _pipeline );

GfxGPUBuffer gfxCreateGPUBuffer( GfxGPUBuffer _buffer, GfxGPUBufferDesc* _desc );
void gfxDestroyGPUBuffer( GfxGPUBuffer _buffer );
		
void gfxBindBuffer( GfxGPUBuffer _buffer );
void gfxBindBufferIndex( GfxGPUBuffer _buffer, int32_t _bindingIndex );

void gfxBufferData( GfxGPUBuffer _buffer, void* _pData, size_t _size );
void gfxBufferSubData( GfxGPUBuffer _buffer, void* _pData, size_t _size, size_t _base );

void gfxCopyBufferSubData( GfxGPUBuffer _readBuffer, GfxGPUBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size );

GfxTexture gfxCreateTexture( GfxTexture _texture, GfxTextureDesc* _pDesc );
void gfxBufferTextureData( GfxTexture _texture, void* _pData, int _generateMipMaps );
void gfxDestroyTexture( GfxTexture _texture );
void gfxBindTextureToSlot( GfxTexture _texture, unsigned int _slot );

void gfxBindVertexBuffer( GfxGPUBuffer _vertexPullBuffer );

void gfxSetFillMode( GfxFillMode _mode );

void gfxDraw( uint32_t _firstVertex, uint32_t _numVertices );
void gfxDrawIndexed( uint32_t _numIndices );
void gfxDrawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
void gfxDrawMultiIndirect( GfxDrawList _drawList );