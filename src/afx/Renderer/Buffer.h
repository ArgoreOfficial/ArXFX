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

struct BufferData;

struct Buffer
{
	BufferType type;
	BufferUsage usage;

	uint32_t count;
	uint32_t stride;
	int32_t  size;

	BufferData* pData;
};


}
