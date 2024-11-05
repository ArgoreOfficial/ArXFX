#pragma once

typedef void* ( *GLloadproc )( const char* name );
void argGfxLoadOpenGL( GLloadproc _loadProc );

#define OBJECT_ALLOC_FUNC( _handle, _buffer, _max ) \
static _handle allocate##_handle()                  \
{                                                   \
	for( size_t i = 0; i < _max; i++ )              \
		if( _buffer[ i ].handle == 0 )              \
			return i + 1;                           \
	return 0;                                       \
}

#define ARG_GFX_MAX_PROGRAMS 128
#define ARG_GFX_MAX_GPU_BUFFERS 128
#define ARG_GFX_MAX_PIPELINES 128
