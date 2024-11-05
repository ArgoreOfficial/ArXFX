#pragma once

#include <types.h>

#if !defined( ARG_GFX_STACK_ALLOCATED_OBJECTS ) and !defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
#define ARG_GFX_STACK_ALLOCATED_OBJECTS
#endif

#if defined( ARG_GFX_STACK_ALLOCATED_OBJECTS )
#define ARG_GFX_HANDLE( _name ) typedef uint16_t _name
#elif defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
#define ARG_GFX_HANDLE( _name ) typedef void* _name
#endif

#define ARG_GFX_FDEC( _name ) typedef struct _name _name

typedef unsigned short bufferBindingIndex_t;

ARG_GFX_FDEC( ArgGfxTextureDesc );
ARG_GFX_FDEC( ArgGfxTextureObject );
ARG_GFX_HANDLE( ArgGfxTexture );

ARG_GFX_FDEC( ArgGfxPipelineDesc );
ARG_GFX_FDEC( ArgGfxPipelineObject );
ARG_GFX_HANDLE( ArgGfxPipeline );

ARG_GFX_FDEC( ArgGfxProgramDesc );
ARG_GFX_FDEC( ArgGfxProgramObject );
ARG_GFX_HANDLE( ArgGfxProgram );

ARG_GFX_FDEC( ArgGfxRenderTargetDesc );
ARG_GFX_FDEC( ArgGfxRenderTargetObject );
ARG_GFX_HANDLE( ArgGfxRenderTarget );

ARG_GFX_FDEC( ArgGfxBufferDesc );
ARG_GFX_FDEC( ArgGfxBufferObject );
ARG_GFX_HANDLE( ArgGfxBuffer );

ARG_GFX_FDEC( ArgGfxVertexAttrib );
ARG_GFX_FDEC( ArgGfxVertexLayout );

typedef enum ArgGfxFillMode
{
	ARG_GFX_FILL_MODE_SOLID,
	ARG_GFX_FILL_MODE_WIREFRAME,
	ARG_GFX_FILL_MODE_POINTS
} ArgGfxFillMode;

typedef enum ArgGfxClearMask
{
	ARG_GFX_CLEAR_MASK_COLOR = 1,
	ARG_GFX_CLEAR_MASK_DEPTH = 2
} ArgGfxClearMask;