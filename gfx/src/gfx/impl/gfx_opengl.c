#include "gfx_opengl.h"

#include "../gfx.h"

#include <glad/glad.h>

void gfxViewport_opengl( int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
}

void gfxSetClearColor_opengl( float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );
}

void gfxClearRenderTarget_opengl( GfxClearMask _mask )
{
	GLbitfield mask = 0;
	if ( _mask && GFX_CLEAR_MASK_COLOR ) mask |= GL_COLOR_BUFFER_BIT;
	if ( _mask && GFX_CLEAR_MASK_DEPTH ) mask |= GL_DEPTH_BUFFER_BIT;

	glClear( mask );
}

void gfxLoadOpenGL( GLloadproc _loadProc )
{
	gladLoadGLLoader( _loadProc );

	gfxViewport = gfxViewport_opengl;
	gfxSetClearColor = gfxSetClearColor_opengl;
	gfxClearRenderTarget = gfxClearRenderTarget_opengl;
}

