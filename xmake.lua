set_languages( "c17" )
set_symbols( "debug" );

add_requires( "glfw" )
add_rules("plugin.vsxmake.autoupdate")

set_targetdir "bin"
set_objectdir "build/obj"

target "gfx"
    set_kind "binary"
    set_default(true)

    add_files( "gfx/src/**.c", "gfx/libs/**.c" )
    add_headerfiles( "gfx/src/**.h", "gfx/libs/**.h" )
    add_filegroups("src/", { rootdir="gfx/src/" } )
    add_filegroups("libs/", { rootdir="gfx/libs/" } )
    
    add_packages( "glfw" )
    add_includedirs( "gfx/src/", "gfx/libs/glad/include/" )
target_end()

target "gfx_hgen"
    set_kind "binary"
    
    add_files( "gfx_hgen/**.c" )
    add_headerfiles( "gfx_hgen/**.h" )
    add_filegroups("./", { rootdir="gfx_hgen/" } )
target_end()