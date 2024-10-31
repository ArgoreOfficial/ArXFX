#ifndef _ARG_GFX_PIPELINE_H
#define _ARG_GFX_PIPELINE_H

#include <gfx/gfx_types.h>

typedef struct ArgGfxPipelineObject
{
	ArgHandle handle;
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
	ArgGfxVertexLayout* pVertexLayout;
} ArgGfxPipelineObject;

typedef struct ArgGfxPipelineDesc
{
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
	ArgGfxVertexLayout* pVertexLayout;
} ArgGfxPipelineDesc;

#endif