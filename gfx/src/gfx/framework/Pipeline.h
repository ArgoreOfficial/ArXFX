#pragma once

#include "../gfx_types.h"

typedef struct sGfxPipeline
{
	GfxHandle handle;
	const char* name;
	sGfxProgram* vertexProgramID;
	sGfxProgram* fragmentProgramID;

	void* pPlatformData;
} sGfxPipeline;

typedef struct sGfxPipelineDesc
{
	const char* name;
	sGfxVertexLayout* pVertexLayout;
	sGfxProgram* vertexProgramID;
	sGfxProgram* fragmentProgramID;

	bool reflect;
} sGfxPipelineDesc;

