function on_config( _target )
    local root = "./"

    _target:set( "languages", "c17", "cxx20" )
    _target:add( "defines", "AFX_C17", "AFX_CPP20" )
    _target:add( "defines", "AFX_PLATFORM_WINDOWS" )

    _target:add( "defines", "AFX_SUPPORT_OPENGL", "AFX_SUPPORT_OPENGLES" )

    -- add supports
    --_target:add( "deps", "GLAD" )
    _target:add( "files", "./libs/**.c" )
    _target:add( "headerfiles", "./libs/**.h" )
    _target:add( "includedirs", "./libs/glad/include/" )
    
	_target:set( "targetdir", "./bin/Windows/$(mode)" )
	_target:set( "objectdir", "./build/obj/Windows/$(mode)" )

    if _target:is_arch( "x64" ) then
        import( root .. "x64.modules.support.glfw" )( _target )

        -- icon resource
        _target:add( "files", "$(projectdir)\\resources\\resource.rc" )
        _target:add( "filegroups", "Resources", { rootdir = "$(projectdir)" } ) -- TODO: allow x86 icon resource

    elseif _target:is_arch( "x86" ) and os.arch() == "x64" then
        _target:add( "ldflags", "-static-libgcc -static-libstdc++" )
        
        _target:add( "linkdirs", "C:/msys64/mingw32/bin/" )
        _target:add( "linkdirs", "C:/msys64/mingw32/lib/" )

    end

    import( root.."x64.modules.support.imgui" )( _target ) 
    --import(root.."support.libsdl")(_target) 
    --import(root.."support.joltphysics")(_target) 
end