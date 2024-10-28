#pragma once


#include "../gfx_types.h"

///////////////////////////////////////////////////////////////////////////////////////

typedef enum GfxShaderProgramType
{
	GFX_SHADER_TYPE_VERTEX,
	GFX_SHADER_TYPE_FRAGMENT
} GfxShaderProgramType;

typedef struct GfxProgramDesc
{
	GfxShaderProgramType type;
	const char* source;
} GfxProgramDesc;

typedef struct GfxProgramObject
{
	GfxHandle handle;
	GfxShaderProgramType type;

	// std::vector<GPUBufferID> shaderBuffers;
	// std::vector<sUniform> textureUniforms;

	void* pPlatformData;
} GfxProgramObject;
