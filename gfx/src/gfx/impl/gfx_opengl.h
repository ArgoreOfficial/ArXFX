#pragma once

#include "../gfx_types.h"

typedef void* ( *GLloadproc )( const char* name );

void gfxViewport_opengl( int _x, int _y, int _width, int _height );
void gfxSetClearColor_opengl( float _r, float _g, float _b, float _a );
void gfxClearRenderTarget_opengl( GfxClearMask _mask );

void gfxLoadOpenGL( GLloadproc _loadProc );
