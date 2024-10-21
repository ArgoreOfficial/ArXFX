#pragma once

#include "../gfx_types.h"

typedef struct sGfxPipeline
{
	GfxHandle handle;
	const char* name;
	GfxProgramID vertexProgramID;
	GfxProgramID fragmentProgramID;

	void* pPlatformData;
} sGfxPipeline;

typedef struct sGfxPipelineDesc
{
	const char* name;
	sGfxVertexLayout* pVertexLayout;
	GfxProgramID vertexProgramID;
	GfxProgramID fragmentProgramID;

	bool reflect;
} sGfxPipelineDesc;

