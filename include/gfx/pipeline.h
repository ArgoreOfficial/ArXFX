#ifndef _ARG_GFX_PIPELINE_H
#define _ARG_GFX_PIPELINE_H

#include <gfx/types.h>

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

ArgGfxPipeline argGfxCreatePipeline( ArgGfxPipeline _pipeline, ArgGfxPipelineDesc* _desc );
void argGfxDestroyPipeline( ArgGfxPipeline _pipeline );
void argGfxBindPipeline( ArgGfxPipeline _pipeline );

#endif