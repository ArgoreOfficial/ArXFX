#pragma once

typedef void* ( *GLloadproc )( const char* name );

void gfxViewport_opengl( int _x, int _y, int _width, int _height );
void gfxClearColor_opengl( float _r, float _g, float _b, float _a );

static void gfxLoadOpenGL( GLloadproc _loadProc )
{
	gladLoadGLLoader( _loadProc );

	gfxViewport = gfxViewport_opengl;
	gfxClearColor = gfxClearColor_opengl;
}
