#pragma once

#include <wv/Types.h>
#include <wv/Graphics/Types.h>
#include <wv/Graphics/Texture.h>

///////////////////////////////////////////////////////////////////////////////////////

namespace wv
{

///////////////////////////////////////////////////////////////////////////////////////

	struct sRenderTargetDesc
	{
		int width = 0;
		int height = 0;
		
		wv::ArgGfxTextureDesc* pTextureDescs = nullptr;
		int numTextures = 0;
	};

///////////////////////////////////////////////////////////////////////////////////////

	struct sRenderTarget
	{
		wv::Handle fbHandle = 0;
		wv::Handle rbHandle = 0;

		wv::TextureID* pTextureIDs = nullptr;
		int numTextures = 0;

		int width = 0;
		int height = 0;

		void* pPlatformData = nullptr;

	};

}


ArgGfxRenderTarget argGfxCreateRenderTarget( ArgGfxRenderTarget _renderTarget, ArgGfxRenderTargetDesc* _desc );
void argGfxDestroyRenderTarget( ArgGfxRenderTarget _renderTarget );
void argGfxSetRenderTarget( ArgGfxRenderTarget _renderTarget );
