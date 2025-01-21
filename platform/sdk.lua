includes "env.lua"

-- Sony PSVita SDK

if SCE_PSP2_SDK_DIR then
	-- print( "Found Sony PSVita SDK" )
    
	includes "platform_psvita.lua"
    includes "toolchains/psvita.lua"
end

-- DEVKITPRO

if DEVKITPRO then

end

-- DEVKITARM 3DS SDK

if DEVKITARM then
	-- print( "Found DEVKITARM SDK" )
	
	includes "platform_3ds.lua"
	includes "toolchains/3ds_arm-none-eabi.lua"	
end