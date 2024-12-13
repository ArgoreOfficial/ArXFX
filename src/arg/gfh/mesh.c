#include <ARG/gfh/mesh.h>

void argGfhCreateMesh( ArgGfxContext _ctx, ArgGfhMesh* _pMesh, ArgGfhMeshDesc* _pDesc )
{
	// create vertex buffer
	ArgGfxBufferDesc vbDesc;
	vbDesc.type = ARG_GFX_BUFFER_TYPE_VERTEX;
	vbDesc.usage = ARG_GFX_BUFFER_USAGE_STATIC_DRAW;
	vbDesc.size = _pDesc->sizeVertices;
	argGfxCreateBuffer( _ctx, &vbDesc, &_pMesh->vertexBuffer );
	argGfxBufferSubData( _ctx, _pMesh->vertexBuffer, _pDesc->pVertices, vbDesc.size, 0 );

	// create index buffer
	ArgGfxBufferDesc ibDesc;
	ibDesc.type = ARG_GFX_BUFFER_TYPE_INDEX;
	ibDesc.usage = ARG_GFX_BUFFER_USAGE_STATIC_DRAW;
	ibDesc.size = sizeof( unsigned int ) * _pDesc->numIndices;
	argGfxCreateBuffer( _ctx, &ibDesc, &_pMesh->indexBuffer );
	argGfxBufferSubData( _ctx, _pMesh->indexBuffer, _pDesc->pIndices, ibDesc.size, 0 );
}

void argGfhBindMesh( ArgGfxContext _ctx, ArgGfhMesh* _pMesh )
{
	argGfxBindBuffer( _ctx, _pMesh->vertexBuffer );
	argGfxBindBuffer( _ctx, _pMesh->indexBuffer );
}
