#pragma once

#include "../gfx_funcdefs.h"
#include "../gfx_types.h"

void gfxViewport_opengl( int _x, int _y, int _width, int _height );

GfxRenderTarget gfxCreateRenderTarget_opengl( GfxRenderTarget _renderTarget, GfxRenderTargetDesc* _desc );
void gfxDestroyRenderTarget_opengl( GfxRenderTarget _renderTarget );
void gfxSetRenderTarget_opengl( GfxRenderTarget _renderTarget );

void gfxSetClearColor_opengl( float _r, float _g, float _b, float _a );
void gfxClearRenderTarget_opengl( GfxClearMask _mask );

GfxProgram gfxCreateProgram_opengl( GfxProgram _program, GfxProgramDesc* _desc );
void gfxDestroyProgram_opengl( GfxProgram _program );

GfxPipeline gfxCreatePipeline_opengl( GfxPipeline _pipeline, GfxPipelineDesc* _desc );
void gfxDestroyPipeline_opengl( GfxPipeline _pipeline );
void gfxBindPipeline_opengl( GfxPipeline _pipeline );

GfxGPUBuffer gfxCreateGPUBuffer_opengl( GfxGPUBuffer _buffer, GfxGPUBufferDesc* _desc );
void gfxDestroyGPUBuffer_opengl( GfxGPUBuffer _buffer );

void gfxBindBuffer_opengl( GfxGPUBuffer _buffer );
void gfxBindBufferIndex_opengl( GfxGPUBuffer _buffer, int32_t _bindingIndex );

void gfxBufferData_opengl( GfxGPUBuffer _buffer, void* _pData, size_t _size );
void gfxBufferSubData_opengl( GfxGPUBuffer _buffer, void* _pData, size_t _size, size_t _base );

void gfxCopyBufferSubData_opengl( GfxGPUBuffer _readBuffer, GfxGPUBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size );

GfxTexture gfxCreateTexture_opengl( GfxTexture _texture, GfxTextureDesc* _pDesc );
void gfxBufferTextureData_opengl( GfxTexture _texture, void* _pData, int _generateMipMaps );
void gfxDestroyTexture_opengl( GfxTexture _texture );
void gfxBindTextureToSlot_opengl( GfxTexture _texture, unsigned int _slot );

void gfxBindVertexBuffer_opengl( GfxGPUBuffer _vertexPullBuffer );

void gfxSetFillMode_opengl( GfxFillMode _mode );

void gfxDraw_opengl( uint32_t _firstVertex, uint32_t _numVertices );
void gfxDrawIndexed_opengl( uint32_t _numIndices );
void gfxDrawIndexedInstanced_opengl( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
//void gfxDrawMultiIndirect( GfxDrawList _drawList );

typedef void* ( *GLloadproc )( const char* name );
void gfxLoadOpenGL( GLloadproc _loadProc );