#pragma once

#include <stdint.h>
#include "gfx_types.h"

typedef void (*gfxViewport_t)( int _x, int _y, int _width, int _height );
gfxViewport_t fp_gfxViewport;
#define gfxViewport fp_gfxViewport

typedef GfxRenderTargetID (*gfxCreateRenderTarget_t)( GfxRenderTargetID _renderTargetID, sGfxRenderTargetDesc* _desc );
gfxCreateRenderTarget_t fp_gfxCreateRenderTarget;
#define gfxCreateRenderTarget fp_gfxCreateRenderTarget

typedef void (*gfxDestroyRenderTarget_t)( GfxRenderTargetID _renderTargetID );
gfxDestroyRenderTarget_t fp_gfxDestroyRenderTarget;
#define gfxDestroyRenderTarget fp_gfxDestroyRenderTarget

typedef void (*gfxSetRenderTarget_t)( GfxRenderTargetID _renderTargetID );
gfxSetRenderTarget_t fp_gfxSetRenderTarget;
#define gfxSetRenderTarget fp_gfxSetRenderTarget

typedef void (*gfxSetClearColor_t)( float _r, float _g, float _b, float _a );
gfxSetClearColor_t fp_gfxSetClearColor;
#define gfxSetClearColor fp_gfxSetClearColor

typedef void (*gfxClearRenderTarget_t)( GfxClearMask _mask );
gfxClearRenderTarget_t fp_gfxClearRenderTarget;
#define gfxClearRenderTarget fp_gfxClearRenderTarget

typedef GfxProgramID (*gfxCreateProgram_t)( GfxProgramID _programID, sGfxProgramDesc* _desc );
gfxCreateProgram_t fp_gfxCreateProgram;
#define gfxCreateProgram fp_gfxCreateProgram

typedef void (*gfxDestroyProgram_t)( GfxProgramID _programID );
gfxDestroyProgram_t fp_gfxDestroyProgram;
#define gfxDestroyProgram fp_gfxDestroyProgram

typedef GfxPipelineID (*gfxCreatePipeline_t)( GfxPipelineID _pipelineID, sGfxPipelineDesc* _desc );
gfxCreatePipeline_t fp_gfxCreatePipeline;
#define gfxCreatePipeline fp_gfxCreatePipeline

typedef void (*gfxDestroyPipeline_t)( GfxPipelineID _pipelineID );
gfxDestroyPipeline_t fp_gfxDestroyPipeline;
#define gfxDestroyPipeline fp_gfxDestroyPipeline

typedef void (*gfxBindPipeline_t)( GfxPipelineID _pipelineID );
gfxBindPipeline_t fp_gfxBindPipeline;
#define gfxBindPipeline fp_gfxBindPipeline

typedef GfxGPUBufferID (*gfxCreateGPUBuffer_t)( GfxGPUBufferID _bufferID, sGfxGPUBufferDesc* _desc );
gfxCreateGPUBuffer_t fp_gfxCreateGPUBuffer;
#define gfxCreateGPUBuffer fp_gfxCreateGPUBuffer

typedef void (*gfxDestroyGPUBuffer_t)( GfxGPUBufferID _bufferID );
gfxDestroyGPUBuffer_t fp_gfxDestroyGPUBuffer;
#define gfxDestroyGPUBuffer fp_gfxDestroyGPUBuffer

typedef void (*gfxBindBuffer_t)( GfxGPUBufferID _bufferID );
gfxBindBuffer_t fp_gfxBindBuffer;
#define gfxBindBuffer fp_gfxBindBuffer

typedef void (*gfxBindBufferIndex_t)( GfxGPUBufferID _bufferID, int32_t _bindingIndex );
gfxBindBufferIndex_t fp_gfxBindBufferIndex;
#define gfxBindBufferIndex fp_gfxBindBufferIndex

typedef void (*gfxBufferData_t)( GfxGPUBufferID _bufferID, void* _pData, size_t _size );
gfxBufferData_t fp_gfxBufferData;
#define gfxBufferData fp_gfxBufferData

typedef void (*gfxBufferSubData_t)( GfxGPUBufferID _bufferID, void* _pData, size_t _size, size_t _base );
gfxBufferSubData_t fp_gfxBufferSubData;
#define gfxBufferSubData fp_gfxBufferSubData

typedef void (*gfxCopyBufferSubData_t)( GfxGPUBufferID _readBufferID, GfxGPUBufferID _writeBufferID, size_t _readOffset, size_t _writeOffset, size_t _size );
gfxCopyBufferSubData_t fp_gfxCopyBufferSubData;
#define gfxCopyBufferSubData fp_gfxCopyBufferSubData

typedef GfxTextureID (*gfxCreateTexture_t)( GfxTextureID _textureID, sGfxTextureDesc* _pDesc );
gfxCreateTexture_t fp_gfxCreateTexture;
#define gfxCreateTexture fp_gfxCreateTexture

typedef void (*gfxBufferTextureData_t)( GfxTextureID _textureID, void* _pData, int _generateMipMaps );
gfxBufferTextureData_t fp_gfxBufferTextureData;
#define gfxBufferTextureData fp_gfxBufferTextureData

typedef void (*gfxDestroyTexture_t)( GfxTextureID _textureID );
gfxDestroyTexture_t fp_gfxDestroyTexture;
#define gfxDestroyTexture fp_gfxDestroyTexture

typedef void (*gfxBindTextureToSlot_t)( GfxTextureID _textureID, unsigned int _slot );
gfxBindTextureToSlot_t fp_gfxBindTextureToSlot;
#define gfxBindTextureToSlot fp_gfxBindTextureToSlot

typedef void (*gfxBindVertexBuffer_t)( GfxGPUBufferID _vertexPullBufferID );
gfxBindVertexBuffer_t fp_gfxBindVertexBuffer;
#define gfxBindVertexBuffer fp_gfxBindVertexBuffer

typedef void (*gfxSetFillMode_t)( GfxFillMode _mode );
gfxSetFillMode_t fp_gfxSetFillMode;
#define gfxSetFillMode fp_gfxSetFillMode

typedef void (*gfxDraw_t)( uint32_t _firstVertex, uint32_t _numVertices );
gfxDraw_t fp_gfxDraw;
#define gfxDraw fp_gfxDraw

typedef void (*gfxDrawIndexed_t)( uint32_t _numIndices );
gfxDrawIndexed_t fp_gfxDrawIndexed;
#define gfxDrawIndexed fp_gfxDrawIndexed

typedef void (*gfxDrawIndexedInstanced_t)( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
gfxDrawIndexedInstanced_t fp_gfxDrawIndexedInstanced;
#define gfxDrawIndexedInstanced fp_gfxDrawIndexedInstanced

