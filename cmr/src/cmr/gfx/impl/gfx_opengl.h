#pragma once

#include "../gfx_funcdefs.h"
#include "../gfx_types.h"

void argGfxViewport_opengl( int _x, int _y, int _width, int _height );

ArgGfxRenderTarget argGfxCreateRenderTarget_opengl( ArgGfxRenderTarget _renderTarget, ArgGfxRenderTargetDesc* _desc );
void argGfxDestroyRenderTarget_opengl( ArgGfxRenderTarget _renderTarget );
void argGfxSetRenderTarget_opengl( ArgGfxRenderTarget _renderTarget );

void argGfxSetClearColor_opengl( float _r, float _g, float _b, float _a );
void argGfxClearRenderTarget_opengl( ArgGfxClearMask _mask );

ArgGfxProgram argGfxCreateProgram_opengl( ArgGfxProgram _program, ArgGfxProgramDesc* _desc );
void argGfxDestroyProgram_opengl( ArgGfxProgram _program );

ArgGfxPipeline argGfxCreatePipeline_opengl( ArgGfxPipeline _pipeline, ArgGfxPipelineDesc* _desc );
void argGfxDestroyPipeline_opengl( ArgGfxPipeline _pipeline );
void argGfxBindPipeline_opengl( ArgGfxPipeline _pipeline );

ArgGfxGPUBuffer argGfxCreateGPUBuffer_opengl( ArgGfxGPUBuffer _buffer, ArgGfxGPUBufferDesc* _desc );
void argGfxDestroyGPUBuffer_opengl( ArgGfxGPUBuffer _buffer );

void argGfxBindBuffer_opengl( ArgGfxGPUBuffer _buffer );
void argGfxBindBufferIndex_opengl( ArgGfxGPUBuffer _buffer, int32_t _bindingIndex );

void argGfxBufferData_opengl( ArgGfxGPUBuffer _buffer, void* _pData, size_t _size );
void argGfxBufferSubData_opengl( ArgGfxGPUBuffer _buffer, void* _pData, size_t _size, size_t _base );

void argGfxCopyBufferSubData_opengl( ArgGfxGPUBuffer _readBuffer, ArgGfxGPUBuffer _writeBuffer, size_t _readOffset, size_t _writeOffset, size_t _size );

ArgGfxTexture argGfxCreateTexture_opengl( ArgGfxTexture _texture, ArgGfxTextureDesc* _pDesc );
void argGfxBufferTextureData_opengl( ArgGfxTexture _texture, void* _pData, int _generateMipMaps );
void argGfxDestroyTexture_opengl( ArgGfxTexture _texture );
void argGfxBindTextureToSlot_opengl( ArgGfxTexture _texture, unsigned int _slot );

void argGfxBindVertexBuffer_opengl( ArgGfxGPUBuffer _vertexPullBuffer );

void argGfxSetFillMode_opengl( ArgGfxFillMode _mode );

void argGfxDraw_opengl( uint32_t _firstVertex, uint32_t _numVertices );
void argGfxDrawIndexed_opengl( uint32_t _numIndices );
void argGfxDrawIndexedInstanced_opengl( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );
//void argGfxDrawMultiIndirect( ArgGfxDrawList _drawList );

typedef void* ( *GLloadproc )( const char* name );
void argGfxLoadOpenGL( GLloadproc _loadProc );