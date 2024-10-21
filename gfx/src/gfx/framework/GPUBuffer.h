#pragma once

#include "../gfx_types.h"

typedef enum eGfxGPUBufferType
{
	GFX_BUFFER_TYPE_NONE = 0,
	GFX_BUFFER_TYPE_INDEX,
	GFX_BUFFER_TYPE_VERTEX,
	GFX_BUFFER_TYPE_UNIFORM,
	GFX_BUFFER_TYPE_DYNAMIC
} eGfxGPUBufferType;

typedef enum eGfxGPUBufferUsage
{
	GFX_BUFFER_USAGE_NONE = 0,
	GFX_BUFFER_USAGE_STATIC_DRAW,
	GFX_BUFFER_USAGE_DYNAMIC_DRAW
} eGfxGPUBufferUsage;

typedef struct sGfxGPUBufferDesc
{
	const char* name;
	eGfxGPUBufferType type;
	eGfxGPUBufferUsage usage;
	int32_t size;
} sGfxGPUBufferDesc;

typedef struct sGfxGPUBuffer
{
	const char* name;
	GfxHandle handle;
	eGfxGPUBufferType type;
	eGfxGPUBufferUsage usage;

	uint32_t count;
	uint32_t stride;
	int32_t  size;

	GfxHandle blockIndex;
	bufferBindingIndex_t bindingIndex;
		
	int complete;

	void* pPlatformData;
} sGfxGPUBuffer;
