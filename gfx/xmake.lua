set_languages( "c17" )
set_symbols( "debug" );

add_requires( "glfw" )

target "ghi"
    set_kind "binary"
    add_files( "**.c" )
    add_headerfiles( "**.h" )
    add_includedirs( "src/", "libs/glad/include/" )
    add_packages( "glfw" )