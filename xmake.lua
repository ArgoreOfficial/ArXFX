set_languages( "cxx20" )
set_symbols( "debug" );

add_requires( "glfw", "glm" )
add_rules("plugin.vsxmake.autoupdate")

set_targetdir "bin"
set_objectdir "build/obj"

target "ArXFX"
    set_kind "binary"
    set_default(true)

    add_files( { 
            "src/**.cpp",
            "libs/**.cpp",
            "libs/**.c"
        } )

    add_headerfiles( "src/**.h" )
    add_headerfiles( "libs/**.h" )
    add_headerfiles( "arx/include/**.hpp" )
    
    add_packages( "glfw", "glm" )
    add_includedirs( "src/", "libs/glad/include/" )
target_end()