
function load_platform_windows()
    set_languages( "c17", "cxx20" )
    add_defines( "AFX_C17", "AFX_CPP20" )
    add_defines( "AFX_PLATFORM_WINDOWS" )

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

    add_defines( "AFX_SUPPORT_OPENGL", "AFX_SUPPORT_OPENGLES" )
end

function target_platform_windows( target )
    local root = "./"
    -- add supports
    --target:add( "deps", "GLAD" )
    target:add( "files", "./libs/**.c" )
    target:add( "headerfiles", "./libs/**.h" )
    target:add( "includedirs", "./libs/glad/include/" )
    
    if target:is_arch( "x64" ) then
        import( root .. "platform.support.glfw" )(target)

        -- icon resource
        target:add( "files", "$(projectdir)\\resources\\resource.rc" )
        target:add( "filegroups", "Resources", { rootdir = "$(projectdir)" } ) -- TODO: allow x86 icon resource

    elseif target:is_arch( "x86" ) and os.arch() == "x64" then
        target:add( "ldflags", "-static-libgcc -static-libstdc++" )
        
        target:add( "linkdirs", "C:/msys64/mingw32/bin/" )
        target:add( "linkdirs", "C:/msys64/mingw32/lib/" )

    end

    --import(root.."platform.support.libsdl")(target) 
    import(root.."platform.support.imgui")(target) 
    --import(root.."platform.support.joltphysics")(target) 
end