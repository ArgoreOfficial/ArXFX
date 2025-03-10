includes "sdk.lua"

includes "platform_windows.lua"
includes "platform_wasm.lua"
includes "platform_linux.lua"

if DEVKITARM then
    includes "toolchains/i686-w64-mingw32.lua"  -- win32 toolchain
    includes "toolchains/3ds_arm-none-eabi.lua" -- 3ds toolchain
end

local PLATFORMS = {
    { plat="windows", arch={ "x64", "x86"  }, load=load_platform_windows, target=target_platform_windows },
    { plat="linux",   arch={ "x86_64"      }, load=load_platform_linux,   target=target_platform_linux   },
    { plat="wasm",    arch={ "wasm32"      }, load=load_platform_wasm,    target=target_platform_wasm    },
    { plat="3ds",     arch={ "citra"       }, load=load_platform_3ds,     target=target_platform_3ds     },
    { plat="psvita",  arch={ "psp2"        }, load=load_platform_psvita,  target=target_platform_psvita, run=run_platform_psvita  }
}

function load_platform()

    -- x86 compiler for w64
    if is_arch( "x86" ) and os.arch() == "x64" then
        set_toolchains( "i686-w64-mingw32" )
    end

    -- configure modes
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
        set_strip "all"
    end

    for i=1,#PLATFORMS do 
        if is_arch(table.unpack(PLATFORMS[i].arch)) and PLATFORMS[ i ].load ~= nil then
            PLATFORMS[i].load()
        end
    end

    -- configure defines for each platform
    after_load(function (target)
        import( "core.project.config" )
        import("core.base.option")

        -- target:add( "defines", "AFX_PLATFORM_" .. string.upper( config.plat() ) )
        target:add( "defines", "AFX_ARCH_"     .. string.upper( config.arch() ) )
        target:add( "defines", "AFX_"          .. string.upper( config.mode() ) )

        if option.get("verbose") then
            print( target:name() )
            print( target:get("defines") )
        end
    end)
end

function target_platform(_root)
    for i=1,#PLATFORMS do 
        if is_arch(table.unpack(PLATFORMS[i].arch)) then 
            if PLATFORMS[ i ].target ~= nil then
                on_load( PLATFORMS[i].target )
            end
            if PLATFORMS[ i ].run ~= nil then
                on_run( PLATFORMS[ i ].run )
            end
        end
    end
end


-- 3ds
function init_platform( target )
    if target:is_arch( "3DS-ARM" ) then
        target:add( "files", "source/**.pica", {rule = "3ds.picasso"} )
        target:add( "rules", "3ds.package" )
        target:set( "extension", ".elf" )

        target:add( "includedirs", {
            "D:/dev/3ds/include",
            "C:/devkitpro/libctru/include",
            "D:/dev/3ds/build",
            "C:/devkitPro/devkitARM/arm-none-eabi/include"
        })

        target:add( "linkdirs", "C:/devkitPro/libctru/lib" )
        target:add( "links", "citro3d", "citro2d", "ctru", "m" )
    end
end
