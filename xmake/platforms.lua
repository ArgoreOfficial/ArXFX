add_moduledirs( "./" )

function init_platform()

    -- x86 compiler for w64
    --if is_arch( "x86" ) and os.arch() == "x64" then
    --    set_toolchains( "i686-w64-mingw32" )
    --end

    for _, filepath in ipairs(os.dirs("xmake/*"), path.translate) do
        local split = path.split( filepath )
        local arch_name = split[#split]

        if is_arch( arch_name ) then
            includes( filepath )
            break
        end
    end
end

function config_platform()
    on_load(function( _target )
        local config = import( "core.project.config" )
        local option = import( "core.base.option" )

        if option.get("verbose") then
            print( "on_load", config.arch() )
        end

        local p = import("get_platform_module")()
        if p.on_load then
            p.on_load( _target )
        end
    end)

    on_config(function( _target )
        local config = import( "core.project.config" )
        local option = import( "core.base.option" )
        
        _target:add( "defines", "AFX_PLATFORM_" .. string.upper( config.plat() ) )
        _target:add( "defines", "AFX_ARCH_"     .. string.upper( config.arch() ) )
        _target:add( "defines", "AFX_"          .. string.upper( config.mode() ) )

        if option.get("verbose") then
            print( "on_config", config.arch() )
            print( _target:name() )
            print( _target:get("defines") )
        end

        local p = import("get_platform_module")()
        if p.on_config then
            p.on_config( _target )
        end
    end)
    
    after_build(function( _target )
        local config = import( "core.project.config" )

        if option.get("verbose") then
            print( "after_build", config.arch() )
        end
        
        local p = import("get_platform_module")()
        if p.after_build then
            p.after_build( _target )
        end
    end)
end
