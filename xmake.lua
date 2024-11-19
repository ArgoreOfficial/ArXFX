set_languages( "c11" )
set_symbols( "debug" );

add_requires( "glfw", "glm" )
add_rules("plugin.vsxmake.autoupdate")

set_targetdir "bin"
set_objectdir "build/obj"

target "ArgoreSDK"
    set_kind "binary"
    set_default(true)

    add_files( 
            "arg/src/**.c",
            "libs/**.c"
        )

    add_headerfiles( 
            "arg/include/**.h", 
            "libs/**.h"
        )
    
    add_packages( "glfw", "glm" )
    add_includedirs( "arg/include/", "libs/glad/include/" )
target_end()