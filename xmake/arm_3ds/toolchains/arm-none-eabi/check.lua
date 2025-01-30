-- imports
import("core.project.config")
import("detect.sdks.find_devkitARM")

-- check the devkitARM toolchain
function main(toolchain)
    local devkitARM
    for _, package in ipairs(toolchain:packages()) do
        local installdir = package:installdir()
        if installdir and os.isdir(installdir) then
            devkitARM = find_devkitARM(installdir, {verbose = true, cross = toolchain:cross()})
            if devkitARM then
                break
            end
        end
    end
    
    if not devkitARM then
        devkitARM = find_devkitARM(
            toolchain:config("devkitARM") or config.get("devkitARM"), 
            { 
                verbose = true, 
                bindir = toolchain:bindir(), 
                cross = toolchain:cross() 
            } )
    end

    if devkitARM then
        toolchain:config_set( "devkitARM", devkitARM.sdkdir )
        toolchain:config_set( "cross", devkitARM.cross )
        toolchain:config_set( "bindir", devkitARM.bindir )
        toolchain:configs_save()
        return true
    end
end