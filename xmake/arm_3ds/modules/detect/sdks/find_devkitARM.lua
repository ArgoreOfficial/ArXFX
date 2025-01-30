-- imports
import("core.base.semver")
import("core.base.option")
import("core.base.global")
import("core.project.config")
import("core.cache.detectcache")
import("lib.detect.find_file")

-- find sdk directory

function _find_devkitpro( sdkdir )
    local devkitpro = os.getenv( "DEVKITPRO" )
    if devkitpro then
        devkitpro = devkitpro:gsub("%/opt/", "C:/")
        return devkitpro
    end
end

function _find_devkitarmdir( sdkdir )
    local prodir = _find_devkitpro( sdkdir )
    return path.join( prodir, "devkitARM" )
end

-- find devkitarm
function _find_devkitarm(sdkdir)

    -- find sdk root directory
    sdkdir = _find_devkitarmdir(sdkdir)
    if not sdkdir then
        return {}
    end
    
    -- find toolchain directory
    local bindir
    local subdirs = {}
    table.insert(subdirs, path.join("*", "bin"))
    
    local gcc = find_file( "arm-none-eabi-gdb-add-index", sdkdir, { suffixes = subdirs } )
    
    if gcc then
        bindir = path.directory(gcc)
    else
        bindir = path.join( sdkdir, "bin" )
    end
    print(sdkdir, ":", bindir)
    return { sdkdir = sdkdir, bindir = bindir }

end

function main(sdkdir, opt)
    -- init arguments
    opt = opt or {}

    -- find sdk
    local sdk = _find_devkitarm(sdkdir or config.get("devkitarm") or global.get("devkitarm"))
    if sdk and sdk.sdkdir then
        config.set("devkitarm", sdk.sdkdir, {force = true, readonly = true})
        if opt.verbose or option.get("verbose") then
            cprint("checking for devkitarm directory ... ${color.success}%s", sdk.sdkdir)
        end
    else
        if opt.verbose or option.get("verbose") then
            cprint("checking for devkitarm directory ... ${color.nothing}${text.nothing}")
        end
    end

    return sdk
end