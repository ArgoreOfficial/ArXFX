#ifndef _ARG_GFX_VERTEX_LAYOUT_H
#define _ARG_GFX_VERTEX_LAYOUT_H

#include <types.h>

typedef struct ArgGfxVertexAttrib
{
	const char* name;
	unsigned int componentCount;
	ArgType type;
	bool normalized;
	unsigned int size;
} ArgGfxVertexAttrib;

typedef struct ArgGfxVertexLayout
{
	ArgGfxVertexAttrib* attributes;
	unsigned int numAttributes;
	unsigned int stride;
} ArgGfxVertexLayout;

void argGfxBindVertexLayout( ArgGfxVertexLayout* _pVertexLayout );

#endif