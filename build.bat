@echo off

"cmr/hgen" "cmr/funcs.h" "cmr/src/cmr/gfx/gfx_funcdefs.h" "OpenGL PSVita"

xmake f --vs=2022
xmake project -k vsxmake -y -m "Debug" -a "x64" ./build