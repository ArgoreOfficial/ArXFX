

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

add_platformdirs("./platforms/")
add_toolchaindirs("./toolchains/")
add_moduledirs("./modules/")
