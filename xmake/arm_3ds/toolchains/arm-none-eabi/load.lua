function main(toolchain)
    local ARCH = { 
        "-march=armv6k", 
        "-mtune=mpcore", 
        "-mfloat-abi=hard", 
        "-mtp=soft" 
        }
    
    local CFLAGS = {
        "-g", 
        "-Wall", 
        "-O2", 
        "-mword-relocations", 
        "-ffunction-sections"
    }
    
    local CXXFLAGS = {
        "-MMD",
        "-MP",
        "-fno-rtti",
        "-fno-exceptions",
        "-std=gnu++11"
    }

    local LDFLAGS = {
        "-specs=3dsx.specs", 
        "-g",
        "-Wl,-Map,build/map.map"
    }    

    toolchain:add( "cflags", CFLAGS, ARCH )
    toolchain:add( "cxxflags", CFLAGS, CXXFLAGS, ARCH )
    toolchain:add( "ldflags", LDFLAGS, ARCH )
    
    import("detect.sdks.find_devkitARM")
    local dkARM = find_devkitARM().sdkdir
    local dkPRO = path.directory( dkARM )

    toolchain:add( "defines", "__3DS__ " )

    -- temporary
    toolchain:add( "includedirs", {
        path.join( dkPRO, "/libctru/include" ), 
        path.join( dkARM, "/include" ), 
        path.join( dkARM, "/arm-none-eabi/include" ), 
        path.join( dkARM, "/arm-none-eabi/include/c++/14.2.0" ), 
        path.join( dkARM, "/arm-none-eabi/include/c++/14.2.0/arm-none-eabi" ), 
        path.join( dkARM, "/lib/gcc/arm-none-eabi/14.2.0/include" )
    })

    print( "dkARM", dkARM )

    toolchain:add( "linkdirs", path.join( dkPRO, "/libctru/lib" ) )
    toolchain:add( "syslinks", "citro3d", "citro2d", "ctru", "m" )
end