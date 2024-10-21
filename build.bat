@echo off

"gfx/gfx_hgen" "gfx/funcs.h" "gfx/src/gfx/gfx_funcdefs.h" "OpenGL PSVita"

xmake f --vs=2022
xmake project -k vsxmake -y -m "Debug" -a "x64" ./build