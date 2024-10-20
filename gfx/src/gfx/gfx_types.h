#pragma once

typedef unsigned short PipelineID;
typedef unsigned short RenderTargetID;
typedef unsigned short ProgramID;
typedef unsigned short GPUBufferID;
typedef unsigned short TextureID;
typedef unsigned short MeshID;

typedef unsigned short BufferBindingIndex;

typedef struct sMeshDesc sMeshDesc;
typedef struct sMeshNode sMeshNode;
typedef struct sMesh sMesh;
typedef struct sTextureDesc sTextureDesc;
typedef struct sTexture sTexture;
typedef struct sPipelineDesc sPipelineDesc;
typedef struct sPipeline sPipeline;
typedef struct sProgramDesc sProgramDesc;
typedef struct sProgram sProgram;
typedef struct sRenderTargetDesc sRenderTargetDesc;
typedef struct sRenderTarget sRenderTarget;
typedef struct sGPUBufferDesc sGPUBufferDesc;

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