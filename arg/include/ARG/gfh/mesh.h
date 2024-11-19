#pragma once

#include <ARG/gfx.h>

typedef struct ArgGfhMesh
{
	ArgGfxBuffer vertexBuffer;
	ArgGfxBuffer indexBuffer;
} ArgGfhMesh;

typedef struct ArgGfhMeshDesc
{
	void* pVertices;
	size_t sizeVertices;

	unsigned int* pIndices;
	int numIndices;
} ArgGfhMeshDesc;

void argGfhCreateMesh( ArgGfxContext _ctx, ArgGfhMesh* _pMesh, ArgGfhMeshDesc* _pDesc );
void argGfhBindMesh( ArgGfxContext _ctx, ArgGfhMesh* _pMesh );