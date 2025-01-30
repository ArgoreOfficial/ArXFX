import("lib.detect.find_program")
import("lib.detect.find_programver")
import("detect.sdks.find_devkitARM")

function main(opt)

    -- init options
    opt = opt or {}

    -- init the search directories
    local sdk = find_devkitARM()
    if sdk and sdk.bindir then
        local paths = {}
        table.insert(paths, sdk.bindir)
        opt.paths = paths
    end

    -- find program
    local program = find_program(opt.program or "arm-none-eabi-g++", opt)

    -- find program version
    local version = nil
    if program and opt and opt.version then
        version = find_programver(program, opt)
    end
    return program, version
end