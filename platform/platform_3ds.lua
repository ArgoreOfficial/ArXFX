includes "env.lua"

rule("3ds.picasso")
    set_extensions( ".pica" )
    
    on_build_file(function (target, sourcefile, opt)
        import("core.project.depend")
        local penv = import("./platform.env")
        local DEVKITPRO = penv.get_safe_env("DEVKITPRO")
        local DEVKITARM = penv.get_safe_env("DEVKITARM")
        
        -- make sure build directory exists
        os.mkdir(target:targetdir())
        
        local filename = path.basename(sourcefile)
        local shbinFile = "build/" .. filename .. ".shbin"
        local headerFile = "include/" .. filename .. ".h"
        local tmpFile = "build/tmp/" .. filename .. ".shbin.tmp"
        local oFile = shbinFile .. ".o"

        print( sourcefile .. " > " .. headerFile )
        os.vrunv( "C:/devkitPro/tools/bin/picasso", { "-o", shbinFile, sourcefile})
        os.vrunv( "C:/devkitPro/tools/bin/bin2s", {
                "-a 4",
                "-H", headerFile,
                shbinFile
            }, 
            table.join(opt, {stdout = tmpFile})
            )
        os.vrunv( DEVKITARM .."/bin/arm-none-eabi-gcc", {
                "-x", "assembler-with-cpp",
                "-g",
                "-march=armv6k", "-mtune=mpcore", "-mfloat-abi=hard", "-mtp=soft",
                "-c", tmpFile,
                "-o", oFile
            })
        table.insert(target:objectfiles(), oFile)
    end)
rule_end()

rule("3ds.package")
    after_build(function(target)
        local penv = import("./platform.env")
        local DEVKITPRO = penv.get_safe_env("DEVKITPRO")
        local DEVKITARM = penv.get_safe_env("DEVKITARM")

        local namepath = target:targetdir() .. "/" .. target:basename()

        os.vrunv(DEVKITARM .."/bin/arm-none-eabi-gcc-nm", { 
            "-CSn", namepath .. ".elf"
            }, {stdout = namepath .. ".lst"} )

        os.vrunv("C:/devkitPro/tools/bin/3dsxtool", { 
            namepath .. ".elf",
            namepath .. ".3dsx",
            -- "--smdh=/d/dev/3ds/3ds.smdh"
            })
    end)
rule_end()

function load_platform_3ds()
    set_toolchains( "arm-none-eabi" )
    add_rules( "3ds.package" )
end

function target_platform_3ds( target )
    local root = "../"
    
    local penv = import("./platform.env")
    local DEVKITPRO = penv.get_safe_env("DEVKITPRO")
    local DEVKITARM = penv.get_safe_env("DEVKITARM")

	target:set( "targetdir", "./bin/3DS/$(mode)" )
	target:set( "objectdir", "./build/obj/3DS/$(mode)" )

    target:add( "includedirs", {
            DEVKITPRO .. "/libctru/include", 
            DEVKITARM .. "/include", 
            DEVKITARM .. "/arm-none-eabi/include", 
            
            --DEVKITARM .. "/arm-none-eabi/include/c++/14.2.0", 
            DEVKITARM .. "/arm-none-eabi/include/c++/14.2.0/arm-none-eabi", 
            DEVKITARM .. "/lib/gcc/arm-none-eabi/14.2.0/include"
        })

    -- add supports
    target:add( "linkdirs", "C:/devkitPro/libctru/lib" )
    target:add( "links", "citro3d", "citro2d", "ctru", "m" )

    target:add( "rules", "3ds.package" )
    target:set( "extension", ".elf" )    
end