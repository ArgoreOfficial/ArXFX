#pragma once

#include <afx/Common.h>

namespace afx {

enum ShaderModuleType
{
	kShaderModuleType_VERTEX = 0,
	kFRAGMENT
};

/* vertex.h ? */
struct VertexAttrib
{
	const char* name;
	unsigned int componentCount;
	Type type;
	uint8_t normalized;
	unsigned int size;
};

struct VertexLayout
{
	VertexAttrib* attributes;
	unsigned int numAttributes;
	unsigned int stride;
};

struct ShaderProgramDesc
{
	ShaderModuleType type;
	const char* source;
};

struct ShaderModule
{
	ShaderModuleType type;

	/*GLuint*/ uint32_t handle;
	/*GLenum*/ uint32_t glType;
};

struct ShaderPipeline
{
	ShaderModule vertexProgram;
	ShaderModule fragmentProgram;
	VertexLayout* pVertexLayout;

	/* GLuint */ uint32_t handle;
};

struct ShaderPipelineDesc
{
	ShaderModule vertexProgram;
	ShaderModule fragmentProgram;
	VertexLayout* pVertexLayout;
};

}
