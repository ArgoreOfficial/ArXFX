
PROJECT_NAME = "Sandbox"

set_project( PROJECT_NAME )
set_version( "0.0.1" )

set_symbols "debug"
set_optimize "none"

if is_mode( "Package" ) then
    set_runtimes "MT"
else
    set_runtimes "MTd"
end

set_allowedarchs( "x64",     "psp2", "arm_3ds" )
set_allowedplats( "windows", "psp2", "3ds" )

includes "xmake/platforms.lua"
init_platform()

set_targetdir "bin/$(plat)/$(mode)/"
set_objectdir "build/obj/"

includes( "src/xmake.lua" )
