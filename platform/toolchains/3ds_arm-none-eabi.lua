includes "env.lua"

toolchain("arm-none-eabi")
    set_kind "standalone"

    set_sdkdir( DEVKITARM )
    set_bindir( DEVKITARM .. "bin/" )

    set_toolset( "cc",  DEVKITARM .. "arm-none-eabi-g++" )
    set_toolset( "cxx", DEVKITARM .. "arm-none-eabi-g++" )
    set_toolset( "ld",  DEVKITARM .. "arm-none-eabi-g++" )
    
    add_defines( "__3DS__ " )

    add_cxxflags{ 
        "-MMD",
        "-MP",
        "-g",
        "-Wall",
        "-O2",
        "-mword-relocations",
        "-ffunction-sections",
        "-march=armv6k",
        "-mtune=mpcore",
        "-mfloat-abi=hard",
        "-mtp=soft",
        "-fno-rtti",
        "-fno-exceptions",
        "-std=gnu++11"
    }

    add_ldflags{
        "-specs=3dsx.specs", "-g",
        "-march=armv6k", "-mtune=mpcore", "-mfloat-abi=hard", "-mtp=soft",
        "-Wl,-Map,$(buildir)/map.map"
    }
toolchain_end()
