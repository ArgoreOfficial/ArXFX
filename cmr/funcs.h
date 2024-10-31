#pragma once

#include <stdint.h>
#include <gfx/gfx_types.h>

?
void argGfxViewport( int _x, int _y, int _width, int _height );

ArgGfxRenderTarget argGfxCreateRenderTarget( ArgGfxRenderTarget _renderTarget, ArgGfxRenderTargetDesc* _desc );
void argGfxDestroyRenderTarget( ArgGfxRenderTarget _renderTarget );
void argGfxSetRenderTarget( ArgGfxRenderTarget _renderTarget );

void argGfxSetClearColor( float _r, float _g, float _b, float _a );
void argGfxClearRenderTarget( ArgGfxClearMask _mask );

ArgGfxProgram argGfxCreateProgram( ArgGfxProgram _program, ArgGfxProgramDesc* _desc );
void argGfxDestroyProgram( ArgGfxProgram _program );

ArgGfxPipeline argGfxCreatePipeline( ArgGfxPipeline _pipeline, ArgGfxPipelineDesc* _desc );
void argGfxDestroyPipeline( ArgGfxPipeline _pipeline );
void argGfxBindPipeline( ArgGfxPipeline _pipeline );

ArgGfxBuffer argGfxCreateBuffer( ArgGfxBuffer _buffer, ArgGfxBufferDesc* _desc );
void argGfxDestroyBuffer( ArgGfxBuffer _buffer );

void argGfxBindBuffer( ArgGfxBuffer _buffer );
void argGfxBindBufferIndex( ArgGfxBuffer _buffer, int32_t _bindingIndex );

void argGfxBufferData( ArgGfxBuffer _buffer, void* _pData, size_t _size );
void argGfxBufferSubData( ArgGfxBuffer _buffer, void* _pData, size_t _size, size_t _base );

void argGfxCopyBufferSubData( ArgGfxBuffer _readBuffer, ArgGfxBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size );

ArgGfxTexture argGfxCreateTexture( ArgGfxTexture _texture, ArgGfxTextureDesc* _pDesc );
void argGfxBufferTextureData( ArgGfxTexture _texture, void* _pData, int _generateMipMaps );
void argGfxDestroyTexture( ArgGfxTexture _texture );
void argGfxBindTextureToSlot( ArgGfxTexture _texture, unsigned int _slot );

void argGfxBindVertexBuffer( ArgGfxBuffer _vertexPullBuffer );

void argGfxSetFillMode( ArgGfxFillMode _mode );

void argGfxDraw( uint32_t _firstVertex, uint32_t _numVertices );
void argGfxDrawIndexed( uint32_t _numIndices );
void argGfxDrawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
void argGfxDrawMultiIndirect( ArgGfxDrawList _drawList );