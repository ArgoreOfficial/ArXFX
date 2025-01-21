target "ArXFX"
	set_languages "cxx20"
    set_kind "binary"
    set_default(true)

    add_files( "**.cpp" )
    add_headerfiles( "**.h" )
    
    add_includedirs( "../ArX/include" )
    add_includedirs( "./" )

    target_platform()   
target_end()