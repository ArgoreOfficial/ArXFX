-- Load x64

if is_mode("Debug") then
	set_symbols "debug"
	set_optimize "none"
	set_strip "none"
elseif is_mode("Release") then 
	set_symbols "debug"
	set_optimize "fast"
	set_strip "debug"
elseif is_mode("Package") then 
	set_symbols "none"
	set_optimize "fastest"
	set_strip "debug"
end

add_requires( "glfw", "glm" )
add_requires( "imgui v1.91.0-docking", { 
	configs={
		opengl3 = true,
		glfw    = true,
		sdl2    = false
	}})

if( is_arch( "x64" ) ) then
	add_requires( "glfw" )
end	