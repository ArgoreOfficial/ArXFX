set_languages( "c17" )
set_symbols( "debug" );

add_requires( "glfw" )
add_rules("plugin.vsxmake.autoupdate")

set_targetdir "bin"
set_objectdir "build/obj"

target "cmr"
    set_kind "binary"
    set_default(true)

    add_files( "cmr/src/**.c", "cmr/libs/**.c" )
    add_headerfiles( "cmr/src/**.h", "cmr/libs/**.h" )
    add_filegroups("src/", { rootdir="cmr/src/" } )
    add_filegroups("libs/", { rootdir="cmr/libs/" } )
    
    add_packages( "glfw" )
    add_includedirs( "cmr/src/cmr/", "cmr/libs/glad/include/" )
target_end()