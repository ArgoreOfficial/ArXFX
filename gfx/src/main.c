#include <stdio.h>

#include "gfx/gfx.h"
#include "gfx/gfx_opengl.h"

int main()
{
	gfxLoadOpenGL();

	gfxClear( 0 );
	
	return 0;
}