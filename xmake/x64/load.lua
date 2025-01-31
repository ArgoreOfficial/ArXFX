--includes "../toolchains/i686-w64-mingw32.lua"  -- win32 toolchain

function load()
    set_languages( "c17", "cxx20" )
    add_defines( "ARC_C17", "ARC_CPP20" )
    add_defines( "ARC_PLATFORM_WINDOWS" )
    add_defines( "ARC_SUPPORT_OPENGL" )

    if is_mode("Debug") then
        set_symbols "debug"
        set_optimize "none"
        set_strip "none"
    elseif is_mode("Release") then 
        set_symbols "debug"
        set_optimize "fast"
        set_strip "debug"
    elseif is_mode("Package") then 
        set_symbols "none"
        set_optimize "fastest"
        set_strip "debug"
    end
    
    add_requires( "glfw", "glm" )
    add_requires( "imgui v1.91.0-docking", { 
        configs={
            opengl3 = true,
            glfw    = true,
            sdl2    = false
        }})
    
    if( is_arch( "x64" ) ) then
        add_requires( "glfw" )
    end	
    
end

PLATFORMS[ "x64" ] = { 
    plat="windows",
    arch={ "x64", "x86"  },
    load=load
}