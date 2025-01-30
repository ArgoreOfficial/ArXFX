#pragma once

#include <wv/Types.h>
#include <wv/Graphics/Types.h>
#include <wv/Graphics/Texture.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace afx
{

///////////////////////////////////////////////////////////////////////////////////////

	struct sRenderTargetDesc
	{
		int width = 0;
		int height = 0;
		
		afx::ArgGfxTextureDesc* pTextureDescs = nullptr;
		int numTextures = 0;
	};

///////////////////////////////////////////////////////////////////////////////////////

	struct sRenderTarget
	{
		afx::Handle fbHandle = 0;
		afx::Handle rbHandle = 0;

		afx::TextureID* pTextureIDs = nullptr;
		int numTextures = 0;

		int width = 0;
		int height = 0;

		void* pPlatformData = nullptr;

	};

}


ArgGfxRenderTarget argGfxCreateRenderTarget( ArgGfxRenderTarget _renderTarget, ArgGfxRenderTargetDesc* _desc );
void argGfxDestroyRenderTarget( ArgGfxRenderTarget _renderTarget );
void argGfxSetRenderTarget( ArgGfxRenderTarget _renderTarget );
