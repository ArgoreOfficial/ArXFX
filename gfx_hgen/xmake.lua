set_languages( "c17" )
set_symbols( "debug" );

target "gfx_hgen"
    set_kind "binary"
    add_files( "src/**.c" )
    add_headerfiles( "**.h" )
    
    set_targetdir "bin"
    set_objectdir "build/obj"
