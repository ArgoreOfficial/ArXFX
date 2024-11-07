#pragma once

typedef void* ( *GLloadproc )( const char* name );
void argGfxLoadOpenGL( GLloadproc _loadProc );

#define OBJECT_ALLOC_FUNC( _handle, _buffer, _max ) \
static _handle argGfxAllocate##_handle()            \
{                                                   \
	for( size_t i = 0; i < _max; i++ )              \
		if( _buffer[ i ].handle == 0 )              \
			return i + 1;                           \
	return 0;                                       \
} \
static void argGfxDeallocate##_handle( _handle _hndl ) \
{ \
	memset( &_buffer[ _hndl ], 0, sizeof( _buffer[ 0 ] ) ); \
} \

#define ARG_GFX_MAX_PROGRAMS 128
#define ARG_GFX_MAX_GPU_BUFFERS 128
#define ARG_GFX_MAX_PIPELINES 128
