platform("3ds")
    set_os("3ds")
    set_hosts("macosx", "linux", "windows", "bsd")
    set_archs("arm_3ds")

    set_formats("static", "lib$(name).a")
    set_formats("object", "$(name).o")
    set_formats("binary", "$(name).elf")
    
    set_toolchains("arm-none-eabi")
platform_end()