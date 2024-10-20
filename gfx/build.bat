@echo off

gfx_hgen "funcs.h" "src/gfx/gfx.h"

xmake f --vs=2022
xmake project -k vsxmake -y -m "Debug" -a "x64" ./build