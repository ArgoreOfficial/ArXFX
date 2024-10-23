#pragma once

#include <stdint.h>

//#define GFX_ID( _name ) typedef struct _name { uint16_t v; } _name
#define GFX_ID( _name ) typedef uint16_t _name
#define GFX_FDEC( _name ) typedef struct _name _name

typedef unsigned short bufferBindingIndex_t;
typedef uint32_t GfxHandle;

GFX_FDEC( sGfxTextureDesc );
GFX_FDEC( sGfxTexture );

GFX_FDEC( sGfxPipelineDesc );
GFX_FDEC( sGfxPipeline );

GFX_FDEC( GfxProgramDesc );
GFX_FDEC( GfxProgram );

GFX_FDEC( sGfxRenderTargetDesc );
GFX_FDEC( sGfxRenderTarget );

GFX_FDEC( GfxGPUBufferDesc );
GFX_FDEC( sGfxGPUBuffer );

GFX_FDEC( sGfxVertexLayout );

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