#pragma once

#include <wv/Graphics/Types.h>
#include <wv/Graphics/Mesh.h>

#include <vector>

namespace arc
{
	WV_DEFINE_ID( DrawListID );

	struct sDrawIndexedIndirectCommand
	{
		uint32_t indexCount;
		uint32_t instanceCount;
		uint32_t firstIndex;
		int32_t  vertexOffset;
		uint32_t firstInstance;
	};

	struct sDrawIndirectCommand
	{
		uint32_t vertexCount;
		uint32_t instanceCount;
		uint32_t firstVertex;
		uint32_t firstInstance;
	};

	struct sDrawList
	{
		PipelineID pipeline;
		
		BufferID viewDataBufferID;
		BufferID instanceBufferID;
		BufferID vertexBufferID;
		
		std::vector<sDrawIndexedIndirectCommand> cmds;
		std::vector<sMeshInstanceData> instances;
	};
}