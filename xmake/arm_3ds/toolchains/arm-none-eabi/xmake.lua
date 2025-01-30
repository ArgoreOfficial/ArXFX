toolchain("arm-none-eabi")
    set_kind "standalone"
    set_description("Nintendo 3DS arm-none-eabi compiler")

    set_toolset( "cc",  "arm-none-eabi-g++" )
    set_toolset( "cxx", "arm-none-eabi-g++" )
    set_toolset( "ld",  "arm-none-eabi-g++" )
    set_toolset( "strip", "arm-none-eabi-strip" )

    on_check("check")
    on_load("load")
toolchain_end()