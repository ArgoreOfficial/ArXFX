#pragma once

#include <afx/Common.h>

namespace arc {

enum class ShaderModuleType
{
	kVERTEX = 0,
	kFRAGMENT
};


enum class FillMode
{
	kSOLID = 0,
	kWIREFRAME,
	kPOINTS
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
	ShaderModuleID vertexProgram;
	ShaderModuleID fragmentProgram;
	VertexLayout* pVertexLayout;

	/* GLuint */ uint32_t handle;
};

struct ShaderPipelineDesc
{
	ShaderModuleID vertexProgram;
	ShaderModuleID fragmentProgram;
	VertexLayout* pVertexLayout;
};

}
