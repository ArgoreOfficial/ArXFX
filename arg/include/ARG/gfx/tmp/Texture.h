#pragma once

#include <ARG/gfx/types.h>

enum TextureChannels
{
	WV_TEXTURE_CHANNELS_R = 1,
	WV_TEXTURE_CHANNELS_RG,
	WV_TEXTURE_CHANNELS_RGB,
	WV_TEXTURE_CHANNELS_RGBA
};

enum eTextureFormat
{
	WV_TEXTURE_FORMAT_BYTE,
	WV_TEXTURE_FORMAT_INT,
	WV_TEXTURE_FORMAT_FLOAT
};

enum eTextureFiltering
{
	WV_TEXTURE_FILTER_NEAREST,
	WV_TEXTURE_FILTER_LINEAR,
};

class cTextureResource;

struct ArgGfxTextureDesc
{
	TextureChannels   channels  = WV_TEXTURE_CHANNELS_RGB;
	eTextureFormat    format    = WV_TEXTURE_FORMAT_BYTE;
	eTextureFiltering filtering = WV_TEXTURE_FILTER_NEAREST;
	int width = 0;
	int height = 0;
	int numChannels = 0;
	bool generateMipMaps = false;
};

typedef struct ArgGfxTexture
{
	eTextureFiltering m_filtering;

	/* opengl specific */
	ArgHandle textureObjectHandle = 0; 
	uint64_t textureHandle        = 0;
		
	uint8_t* pData = nullptr;
	unsigned int dataSize = 0;

	int width  = 0;
	int height = 0;
	int numChannels = 0;

	void* pPlatformData = nullptr;
} ArgGfxTexture;



ArgGfxTexture argGfxCreateTexture( ArgGfxTexture _texture, ArgGfxTextureDesc* _pDesc );
void argGfxBufferTextureData( ArgGfxTexture _texture, void* _pData, int _generateMipMaps );
void argGfxDestroyTexture( ArgGfxTexture _texture );
void argGfxBindTextureToSlot( ArgGfxTexture _texture, unsigned int _slot );
