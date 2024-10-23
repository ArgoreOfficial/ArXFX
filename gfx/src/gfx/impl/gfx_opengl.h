#pragma once

#include "../gfx_types.h"

typedef void* ( *GLloadproc )( const char* name );

void gfxViewport_opengl( int _x, int _y, int _width, int _height );

GfxRenderTargetID gfxCreateRenderTarget_opengl( GfxRenderTargetID _renderTargetID, sGfxRenderTargetDesc* _desc );
void gfxDestroyRenderTarget_opengl( GfxRenderTargetID _renderTargetID );
void gfxSetRenderTarget_opengl( GfxRenderTargetID _renderTargetID );

void gfxSetClearColor_opengl( float _r, float _g, float _b, float _a );
void gfxClearRenderTarget_opengl( GfxClearMask _mask );

GfxProgram* gfxCreateProgram_opengl( GfxProgramDesc* _desc );
void gfxDestroyProgram_opengl( GfxProgramID _programID );

GfxPipelineID gfxCreatePipeline_opengl( GfxPipelineID _pipelineID, sGfxPipelineDesc* _desc );
void gfxDestroyPipeline_opengl( GfxPipelineID _pipelineID );
void gfxBindPipeline_opengl( GfxPipelineID _pipelineID );

GfxGPUBufferID gfxCreateGPUBuffer_opengl( GfxGPUBufferID _bufferID, GfxGPUBufferDesc* _desc );
void gfxDestroyGPUBuffer_opengl( GfxGPUBufferID _bufferID );

void gfxBindBuffer_opengl( GfxGPUBufferID _bufferID );
void gfxBindBufferIndex_opengl( GfxGPUBufferID _bufferID, int32_t _bindingIndex );

void gfxBufferData_opengl( GfxGPUBufferID _bufferID, void* _pData, size_t _size );
void gfxBufferSubData_opengl( GfxGPUBufferID _bufferID, void* _pData, size_t _size, size_t _base );

void gfxCopyBufferSubData_opengl( GfxGPUBufferID _readBufferID, GfxGPUBufferID _writeBufferID, size_t _readOffset, size_t _writeOffset, size_t _size );

GfxTextureID CreateTexture_opengl( GfxTextureID _textureID, sGfxTextureDesc* _pDesc );
void gfxBufferTextureData_opengl( GfxTextureID _textureID, void* _pData, int _generateMipMaps );
void gfxDestroyTexture_opengl( GfxTextureID _textureID );
void gfxBindTextureToSlot_opengl( GfxTextureID _textureID, unsigned int _slot );

void gfxBindVertexBuffer_opengl( GfxGPUBufferID _vertexPullBufferID );

void gfxSetFillMode_opengl( GfxFillMode _mode );

void gfxDraw_opengl( uint32_t _firstVertex, uint32_t _numVertices );
void gfxDrawIndexed_opengl( uint32_t _numIndices );
void gfxDrawIndexedInstanced_opengl( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
void gfxDrawMultiIndirect_opengl( GfxDrawListID _drawListID );

void gfxLoadOpenGL( GLloadproc _loadProc );
