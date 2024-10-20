#include "gfx.h"
#include "gfx_opengl.h"

#include <glad/glad.h>

void gfxViewport_opengl( int _x, int _y, int _width, int _height )
{
	glViewport( _x, _y, _width, _height );
}

void gfxClearColor_opengl( float _r, float _g, float _b, float _a )
{
	glClearColor( _r, _g, _b, _a );
	glClear( GL_COLOR_BUFFER_BIT );
}

