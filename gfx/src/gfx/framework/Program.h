#pragma once


#include "../gfx_types.h"

///////////////////////////////////////////////////////////////////////////////////////

typedef enum eGfxShaderProgramType
{
	WV_SHADER_TYPE_VERTEX,
	WV_SHADER_TYPE_FRAGMENT
} GfxShaderProgramType;

typedef struct sGfxProgramDesc
{
	GfxShaderProgramType type;
	const char* source;
} GfxProgramDesc;

typedef struct sGfxProgram
{
	GfxHandle handle;
	GfxShaderProgramType type;

	// std::vector<GPUBufferID> shaderBuffers;
	// std::vector<sUniform> textureUniforms;

	void* pPlatformData;
} GfxProgram;
