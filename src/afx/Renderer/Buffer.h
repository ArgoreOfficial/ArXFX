#pragma once

#include <afx/Common.h>

namespace afx {

enum class BufferType
{
	kNONE = 0,
	kINDEX,
	kVERTEX,
	kUNIFORM,
	kDYNAMIC
};

enum class BufferUsage
{
	kNONE = 0,
	kSTATIC_DRAW,
	kDYNAMIC_DRAW
};

struct BufferDesc
{
	BufferType type;
	BufferUsage usage;
	int32_t size;
};


struct Buffer
{
	/*GLuint*/ uint32_t handle;

	BufferType type;
	BufferUsage usage;

	/*GLenum*/ uint32_t glType;
	/*GLenum*/ uint32_t glUsage;

	uint32_t count;
	uint32_t stride;
	int32_t  size;

	/*ArgHandle*/ uint32_t blockIndex;
	/*GLuint*/ uint32_t bindingIndex;
};


}
