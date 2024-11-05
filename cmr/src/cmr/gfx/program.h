#ifndef _ARG_GFX_PROGRAM_H
#define _ARG_GFX_PROGRAM_H

#include <gfx/gfx_types.h>

///////////////////////////////////////////////////////////////////////////////////////

typedef enum ArgGfxShaderProgramType
{
	ARG_GFX_SHADER_TYPE_VERTEX,
	ARG_GFX_SHADER_TYPE_FRAGMENT
} ArgGfxShaderProgramType;

typedef struct ArgGfxProgramDesc
{
	ArgGfxShaderProgramType type;
	const char* source;
} ArgGfxProgramDesc;

typedef struct ArgGfxProgramObject
{
	ArgHandle handle;
	ArgGfxShaderProgramType type;

	// std::vector<BufferID> shaderBuffers;
	// std::vector<sUniform> textureUniforms;

	void* pPlatformData;
} ArgGfxProgramObject;



ArgGfxProgram argGfxCreateProgram( ArgGfxProgram _program, ArgGfxProgramDesc* _desc );

void argGfxDestroyProgram( ArgGfxProgram _program );


#endif