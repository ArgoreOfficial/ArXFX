#pragma once

#include <stdint.h>

typedef struct unordered_array
{
	void* pBuffer;
	size_t size;
	size_t stride;
	uint16_t* usedIDs;
	size_t numIDs;
} unordered_array;

void createUnorderedArray( unordered_array* _pObjectBuffer, size_t _stride, size_t _size );
uint16_t gfxObufGetAvailable();
uint16_t gfxObufAllocate();