#pragma once

#include <stdint.h>

#if !defined( GFX_STACK_ALLOCATED_OBJECTS ) and !defined( GFX_HEAP_ALLOCATED_OBJECTS )
#define GFX_STACK_ALLOCATED_OBJECTS
#endif

#if defined( GFX_STACK_ALLOCATED_OBJECTS )
#define GFX_HANDLE( _name ) typedef uint16_t _name
#elif defined( GFX_HEAP_ALLOCATED_OBJECTS )
#define GFX_HANDLE( _name ) typedef void* _name
#endif

#define GFX_FDEC( _name ) typedef struct _name _name

typedef unsigned short bufferBindingIndex_t;
typedef uint32_t GfxHandle;

GFX_FDEC( GfxTextureDesc );
GFX_FDEC( GfxTextureObject );
GFX_HANDLE( GfxTexture );

GFX_FDEC( GfxPipelineDesc );
GFX_FDEC( GfxPipelineObject );
GFX_HANDLE( GfxPipeline );

GFX_FDEC( GfxProgramDesc );
GFX_FDEC( GfxProgramObject );
GFX_HANDLE( GfxProgram );

GFX_FDEC( GfxRenderTargetDesc );
GFX_FDEC( GfxRenderTargetObject );
GFX_HANDLE( GfxRenderTarget );

GFX_FDEC( GfxGPUBufferDesc );
GFX_FDEC( GfxGPUBufferObject );
GFX_HANDLE( GfxGPUBuffer );

GFX_FDEC( GfxVertexLayout );

typedef enum GfxFillMode
{
	GFX_FILL_MODE_SOLID,
	GFX_FILL_MODE_WIREFRAME,
	GFX_FILL_MODE_POINTS
} GfxFillMode;

typedef enum GfxClearMask
{
	GFX_CLEAR_MASK_COLOR = 1,
	GFX_CLEAR_MASK_DEPTH = 2
} GfxClearMask;