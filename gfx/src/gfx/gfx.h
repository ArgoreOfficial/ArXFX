#pragma once

typedef void ( *gfxViewport_t )( int _x, int _y, int _width, int _height );
gfxViewport_t fp_gfxViewport;
#define gfxViewport fp_gfxViewport

typedef void ( *gfxClearColor_t )( float _r, float _g, float _b, float _a );
gfxClearColor_t fp_gfxClearColor;
#define gfxClearColor fp_gfxClearColor
