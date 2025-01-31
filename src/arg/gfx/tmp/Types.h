#pragma once

#include <wv/Types.h>

#include <wv/Math/Matrix.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace arc
{
	ARC_DEFINE_ID( PipelineID );
	ARC_DEFINE_ID( RenderTargetID );
	ARC_DEFINE_ID( ProgramID );
	ARC_DEFINE_ID( BufferID );
	ARC_DEFINE_ID( TextureID );
	ARC_DEFINE_ID( MeshID );

	ARC_DEFINE_ID( BufferBindingIndex );

	struct sMeshDesc;
	struct sMeshNode;
	struct sMesh;

	struct ArgGfxTextureDesc;
	struct sTexture;

	struct sPipelineDesc;
	struct sPipeline;
	
	struct sProgramDesc;
	struct sProgram;

	struct sRenderTargetDesc;
	struct sRenderTarget;

	struct sBufferDesc;

	/// TODO: move
	struct sUbCameraData
	{
		Matrix4x4f projection;
		Matrix4x4f view;
		Matrix4x4f model;
	};

	enum eFillMode
	{
		ARC_FILL_MODE_SOLID,
		ARC_FILL_MODE_WIREFRAME,
		ARC_FILL_MODE_POINTS
	};

}

