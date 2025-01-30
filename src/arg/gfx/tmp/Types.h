#pragma once

#include <wv/Types.h>

#include <wv/Math/Matrix.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace afx
{
	WV_DEFINE_ID( PipelineID );
	WV_DEFINE_ID( RenderTargetID );
	WV_DEFINE_ID( ProgramID );
	WV_DEFINE_ID( BufferID );
	WV_DEFINE_ID( TextureID );
	WV_DEFINE_ID( MeshID );

	WV_DEFINE_ID( BufferBindingIndex );

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
		WV_FILL_MODE_SOLID,
		WV_FILL_MODE_WIREFRAME,
		WV_FILL_MODE_POINTS
	};

}

