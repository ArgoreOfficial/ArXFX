set_languages( "c17" )
set_symbols( "debug" );

add_requires( "glfw" )
add_rules("plugin.vsxmake.autoupdate")

target "ghi"
    set_kind "binary"
    
    add_files( "src/**.c", "libs/**.c" )
    add_headerfiles( "src/**.h", "libs/**.h" )
    
    add_packages( "glfw" )
    add_includedirs( "src/", "libs/glad/include/" )

    set_targetdir "bin"
    set_objectdir "build/obj"