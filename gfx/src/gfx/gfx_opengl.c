
#include "gfx.h"

#include <stdio.h>
#include "gfx_opengl.h"

void gfxClear_implopengl( unsigned int _mask )
{
	printf( "clear opengl\n" );
}

void gfxLoadOpenGL()
{
	gfxClear = gfxClear_implopengl;
}
