set_languages( "c17" )
set_symbols( "debug" );

target "ghi"
    set_kind "binary"
    add_files( "src/**.c" )
    add_headerfiles( "**.h" )