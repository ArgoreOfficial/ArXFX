function on_config( _target )
    _target:add( "rules", "3ds.package" )
    _target:set( "extension", ".elf" )    

    _target:add( "rules", "3ds" )
    _target:set( "toolchains", "arm-none-eabi" )

    _target:set("plat", "3ds")

    _target:set( "os", "3ds")
    _target:set( "hosts", "macosx", "linux", "windows", "bsd")
    _target:set( "archs", "armv6k", "3ds", "citra")

    _target:set( "formats", "static", "lib$(name).a")
    _target:set( "formats", "object", "$(name).o")
    _target:set( "formats", "binary", "$(name).elf")

    _target:set( "toolchains", "arm-none-eabi")

    if is_mode( "release" ) then
        _target:set("strip", "debug")
    end
end

function on_load( _target )
    _target:set( "toolchains", "arm-none-eabi" )
end

function after_build(_target)
    import("detect.sdks.find_devkitARM")
    local sdk = find_devkitARM()
    local DEVKITARM = sdk.sdkdir

    local namepath = _target:targetdir() .. "/" .. _target:basename()

    os.vrunv(DEVKITARM .."/bin/arm-none-eabi-gcc-nm", { 
        "-CSn", namepath .. ".elf"
        }, {stdout = namepath .. ".lst"} )

    os.vrunv("C:/devkitPro/tools/bin/3dsxtool", { 
        namepath .. ".elf",
        namepath .. ".3dsx",
        -- "--smdh=/d/dev/3ds/3ds.smdh"
        })
end