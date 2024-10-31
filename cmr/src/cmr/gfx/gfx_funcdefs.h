#pragma once

#include <stdint.h>
#include <gfx/gfx_types.h>

typedef void (*argGfxViewport_t)( int _x, int _y, int _width, int _height );
argGfxViewport_t fp_argGfxViewport;
#define argGfxViewport fp_argGfxViewport

typedef ArgGfxRenderTarget (*argGfxCreateRenderTarget_t)( ArgGfxRenderTarget _renderTarget, ArgGfxRenderTargetDesc* _desc );
argGfxCreateRenderTarget_t fp_argGfxCreateRenderTarget;
#define argGfxCreateRenderTarget fp_argGfxCreateRenderTarget

typedef void (*argGfxDestroyRenderTarget_t)( ArgGfxRenderTarget _renderTarget );
argGfxDestroyRenderTarget_t fp_argGfxDestroyRenderTarget;
#define argGfxDestroyRenderTarget fp_argGfxDestroyRenderTarget

typedef void (*argGfxSetRenderTarget_t)( ArgGfxRenderTarget _renderTarget );
argGfxSetRenderTarget_t fp_argGfxSetRenderTarget;
#define argGfxSetRenderTarget fp_argGfxSetRenderTarget

typedef void (*argGfxSetClearColor_t)( float _r, float _g, float _b, float _a );
argGfxSetClearColor_t fp_argGfxSetClearColor;
#define argGfxSetClearColor fp_argGfxSetClearColor

typedef void (*argGfxClearRenderTarget_t)( ArgGfxClearMask _mask );
argGfxClearRenderTarget_t fp_argGfxClearRenderTarget;
#define argGfxClearRenderTarget fp_argGfxClearRenderTarget

typedef ArgGfxProgram (*argGfxCreateProgram_t)( ArgGfxProgram _program, ArgGfxProgramDesc* _desc );
argGfxCreateProgram_t fp_argGfxCreateProgram;
#define argGfxCreateProgram fp_argGfxCreateProgram

typedef void (*argGfxDestroyProgram_t)( ArgGfxProgram _program );
argGfxDestroyProgram_t fp_argGfxDestroyProgram;
#define argGfxDestroyProgram fp_argGfxDestroyProgram

typedef ArgGfxPipeline (*argGfxCreatePipeline_t)( ArgGfxPipeline _pipeline, ArgGfxPipelineDesc* _desc );
argGfxCreatePipeline_t fp_argGfxCreatePipeline;
#define argGfxCreatePipeline fp_argGfxCreatePipeline

typedef void (*argGfxDestroyPipeline_t)( ArgGfxPipeline _pipeline );
argGfxDestroyPipeline_t fp_argGfxDestroyPipeline;
#define argGfxDestroyPipeline fp_argGfxDestroyPipeline

typedef void (*argGfxBindPipeline_t)( ArgGfxPipeline _pipeline );
argGfxBindPipeline_t fp_argGfxBindPipeline;
#define argGfxBindPipeline fp_argGfxBindPipeline

typedef ArgGfxBuffer (*argGfxCreateBuffer_t)( ArgGfxBuffer _buffer, ArgGfxBufferDesc* _desc );
argGfxCreateBuffer_t fp_argGfxCreateBuffer;
#define argGfxCreateBuffer fp_argGfxCreateBuffer

typedef void (*argGfxDestroyBuffer_t)( ArgGfxBuffer _buffer );
argGfxDestroyBuffer_t fp_argGfxDestroyBuffer;
#define argGfxDestroyBuffer fp_argGfxDestroyBuffer

typedef void (*argGfxBindBuffer_t)( ArgGfxBuffer _buffer );
argGfxBindBuffer_t fp_argGfxBindBuffer;
#define argGfxBindBuffer fp_argGfxBindBuffer

typedef void (*argGfxBindBufferIndex_t)( ArgGfxBuffer _buffer, int32_t _bindingIndex );
argGfxBindBufferIndex_t fp_argGfxBindBufferIndex;
#define argGfxBindBufferIndex fp_argGfxBindBufferIndex

typedef void (*argGfxBufferData_t)( ArgGfxBuffer _buffer, void* _pData, size_t _size );
argGfxBufferData_t fp_argGfxBufferData;
#define argGfxBufferData fp_argGfxBufferData

typedef void (*argGfxBufferSubData_t)( ArgGfxBuffer _buffer, void* _pData, size_t _size, size_t _base );
argGfxBufferSubData_t fp_argGfxBufferSubData;
#define argGfxBufferSubData fp_argGfxBufferSubData

typedef void (*argGfxCopyBufferSubData_t)( ArgGfxBuffer _readBuffer, ArgGfxBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size );
argGfxCopyBufferSubData_t fp_argGfxCopyBufferSubData;
#define argGfxCopyBufferSubData fp_argGfxCopyBufferSubData

typedef ArgGfxTexture (*argGfxCreateTexture_t)( ArgGfxTexture _texture, ArgGfxTextureDesc* _pDesc );
argGfxCreateTexture_t fp_argGfxCreateTexture;
#define argGfxCreateTexture fp_argGfxCreateTexture

typedef void (*argGfxBufferTextureData_t)( ArgGfxTexture _texture, void* _pData, int _generateMipMaps );
argGfxBufferTextureData_t fp_argGfxBufferTextureData;
#define argGfxBufferTextureData fp_argGfxBufferTextureData

typedef void (*argGfxDestroyTexture_t)( ArgGfxTexture _texture );
argGfxDestroyTexture_t fp_argGfxDestroyTexture;
#define argGfxDestroyTexture fp_argGfxDestroyTexture

typedef void (*argGfxBindTextureToSlot_t)( ArgGfxTexture _texture, unsigned int _slot );
argGfxBindTextureToSlot_t fp_argGfxBindTextureToSlot;
#define argGfxBindTextureToSlot fp_argGfxBindTextureToSlot

typedef void (*argGfxBindVertexBuffer_t)( ArgGfxBuffer _vertexPullBuffer );
argGfxBindVertexBuffer_t fp_argGfxBindVertexBuffer;
#define argGfxBindVertexBuffer fp_argGfxBindVertexBuffer

typedef void (*argGfxSetFillMode_t)( ArgGfxFillMode _mode );
argGfxSetFillMode_t fp_argGfxSetFillMode;
#define argGfxSetFillMode fp_argGfxSetFillMode

typedef void (*argGfxDraw_t)( uint32_t _firstVertex, uint32_t _numVertices );
argGfxDraw_t fp_argGfxDraw;
#define argGfxDraw fp_argGfxDraw

typedef void (*argGfxDrawIndexed_t)( uint32_t _numIndices );
argGfxDrawIndexed_t fp_argGfxDrawIndexed;
#define argGfxDrawIndexed fp_argGfxDrawIndexed

typedef void (*argGfxDrawIndexedInstanced_t)( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
argGfxDrawIndexedInstanced_t fp_argGfxDrawIndexedInstanced;
#define argGfxDrawIndexedInstanced fp_argGfxDrawIndexedInstanced

