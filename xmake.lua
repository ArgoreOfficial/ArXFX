set_languages( "c17" )
set_symbols( "debug" );

add_requires( "glfw" )
add_rules("plugin.vsxmake.autoupdate")

set_targetdir "bin"
set_objectdir "build/obj"

target "cmr"
    set_kind "binary"
    set_default(true)

    add_files( "src/**.c", "libs/**.c" )
    add_headerfiles( "include/**.h", "libs/**.h" )
    
    add_packages( "glfw" )
    add_includedirs( "include/", "libs/glad/include/" )
target_end()