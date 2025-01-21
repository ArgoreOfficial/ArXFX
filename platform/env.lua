function get_safe_env( _str )
	local v = os.getenv( _str )
	if v then
		v = v:gsub("%/opt/", "C:/")
	end
	return v
end

SCE_PSP2_SDK_DIR = get_safe_env("SCE_PSP2_SDK_DIR")
DEVKITPRO = get_safe_env( "DEVKITPRO" ) -- C:/devkitpro
DEVKITARM = get_safe_env( "DEVKITARM" ) -- C:/devkitpro/devkitARM
