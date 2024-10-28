#pragma once

#include "../gfx_types.h"

typedef enum GfxGPUBufferType
{
	GFX_BUFFER_TYPE_NONE = 0,
	GFX_BUFFER_TYPE_INDEX,
	GFX_BUFFER_TYPE_VERTEX,
	GFX_BUFFER_TYPE_UNIFORM,
	GFX_BUFFER_TYPE_DYNAMIC
} GfxGPUBufferType;

typedef enum GfxGPUBufferUsage
{
	GFX_BUFFER_USAGE_NONE = 0,
	GFX_BUFFER_USAGE_STATIC_DRAW,
	GFX_BUFFER_USAGE_DYNAMIC_DRAW
} GfxGPUBufferUsage;

typedef struct GfxGPUBufferDesc
{
	GfxGPUBufferType type;
	GfxGPUBufferUsage usage;
	int32_t size;
};

typedef struct GfxGPUBufferObject
{
	GfxHandle handle;

	GfxGPUBufferType type;
	GfxGPUBufferUsage usage;

	uint32_t count;
	uint32_t stride;
	int32_t  size;

	GfxHandle blockIndex;
	bufferBindingIndex_t bindingIndex;

	void* pPlatformData;
};
