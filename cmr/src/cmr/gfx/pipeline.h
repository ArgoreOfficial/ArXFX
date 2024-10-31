#ifndef _ARG_GFX_PIPELINE_H
#define _ARG_GFX_PIPELINE_H

#include <gfx/gfx_types.h>

typedef struct ArgGfxPipelineObject
{
	ArgHandle handle;
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
} ArgGfxPipelineObject;

typedef struct ArgGfxPipelineDesc
{
	ArgGfxVertexLayout* pVertexLayout;
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
} ArgGfxPipelineDesc;

#endif