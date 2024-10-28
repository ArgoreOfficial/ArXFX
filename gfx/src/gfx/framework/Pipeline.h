#pragma once

#include "../gfx_types.h"

typedef struct GfxPipelineObject
{
	GfxHandle handle;
	GfxProgram vertexProgram;
	GfxProgram fragmentProgram;
} GfxPipelineObject;

typedef struct GfxPipelineDesc
{
	GfxVertexLayout* pVertexLayout;
	GfxProgram vertexProgram;
	GfxProgram fragmentProgram;
} GfxPipelineDesc;

