#include <stdio.h>

#ifdef AFX_ARCH_X64
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#elif defined(AFX_ARCH_CITRA)
#include <3ds.h>
#include <citro3d.h>
#endif

#include <afx/Renderer/LowLevel/LowLevelGraphics.h>

#ifdef AFX_SUPPORT_GLFW
GLFWwindow* window;
#endif

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// function definitions ///////////////////////////////////////////////////////////////

int initWindow();
void deinitWindow();

///////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T swap_endian( T u )
{
	union
	{
		T u;
		unsigned char u8[ sizeof( T ) ];
	} source, dest;

	source.u = u;

	for ( size_t k = 0; k < sizeof( T ); k++ )
		dest.u8[ k ] = source.u8[ sizeof( T ) - k - 1 ];

	return dest.u;
}
#ifdef AFX_ARCH_CITRA
#define CLEAR_COLOR 0x68B0D8FF

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

union color
{
	struct
	{
		uint8_t r, g, b, a;
	};
	uint32_t i;
};

static const uint8_t colorFmtSizes[] = { 2,1,0,0,0 };
static const uint8_t depthFmtSizes[] = { 0,0,1,2 };

void vkCmdClearColorImage( C3D_FrameBuf* frameBuf, u32 clearColor )
{
	u32 size = (u32)frameBuf->width * frameBuf->height;
	u32 cfs = colorFmtSizes[ frameBuf->colorFmt ];
	void* colorBufEnd = (u8*)frameBuf->colorBuf + size * ( 2 + cfs );

	GX_MemoryFill(
		(u32*)frameBuf->colorBuf,
		clearColor,
		(u32*)colorBufEnd,
		BIT( 0 ) | ( cfs << 8 ),
		NULL, 0, NULL, 0 );
}
#endif
int main()
{
	if ( !initWindow() ) return 1;

	uint32_t frameNumber = 0;
#ifdef AFX_ARCH_X64
	afx::ILowLevelGraphics* g_graphics = afx::ILowLevelGraphics::Registry::createFromName( "OpenGL" );
#elif defined( AFX_ARCH_CITRA )
	afx::ILowLevelGraphics* g_graphics = afx::ILowLevelGraphics::Registry::createFromName( "Citra" );
#endif
	g_graphics->init();
	g_graphics->viewport( 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT );

	afx::CmdBuffer* cmdBuffer = g_graphics->createCmdBuffer();

#ifdef AFX_SUPPORT_GLFW
	while ( !glfwWindowShouldClose( window ) )
	{
		// update screen data buffer
		int width, height;
		glfwGetWindowSize( window, &width, &height );

		g_graphics->viewport( 0, 0, width, height );

		float flash = fabs( sin( frameNumber / 60.0f ) );
		
		afx::Image m{};
		g_graphics->_cmdBegin( *cmdBuffer );
		g_graphics->_cmdImageClear( *cmdBuffer, m, flash, 0.0f, flash, 1.0f );
		g_graphics->_cmdEnd( *cmdBuffer );
		g_graphics->_cmdSubmit( *cmdBuffer );

		// g_graphics->clearColor( flash, 0.0f, flash, 1.0f );

		glfwSwapBuffers( window );
		glfwPollEvents();

		frameNumber++;
	}

	deinitWindow();
#elif defined( AFX_ARCH_CITRA )

	

	consoleInit( GFX_BOTTOM, 0 );
	printf( "test\n" );
	printf( "test2 citra\n" );

	// Initialize the render target
	C3D_RenderTarget* target = C3D_RenderTargetCreate( 240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8 );
	C3D_RenderTargetSetOutput( target, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS );

	// Main loop
	while ( aptMainLoop() )
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if ( kDown & KEY_START )
			break; // break in order to return to hbmenu

		float flash = fabs( sinf( frameNumber / 60.0f ) );

		color c{};
		c.r = flash * 255;
		c.g = 0;
		c.b = flash * 255;
		c.a = 255;

		// Render the scene
		C3D_FrameBegin( C3D_FRAME_SYNCDRAW );
		vkCmdClearColorImage( &target->frameBuf, swap_endian( c.i ) );

		C3D_FrameDrawOn( target );

		C3D_FrameEnd( 0 );
		frameNumber++;
	}

	// Deinitialize graphics
	C3D_Fini();
	gfxExit();
#endif

	return 0;
}

// impl ///////////////////////////////////////////////////////////////////////////////

int initWindow()
{
#ifdef AFX_ARCH_X64
	if ( !glfwInit() )
		return 0;

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, 1 );
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "ArX FX", NULL, NULL );

	glfwMakeContextCurrent( window );

	if ( !window )
	{
		glfwTerminate();
		printf( "failed to create window\n" );
		return 0;
	}

	HWND hWnd = glfwGetWin32Window( window );
	SetWindowDisplayAffinity( hWnd, WDA_NONE );

	glfwSwapInterval( 1 );
#elif defined( AFX_ARCH_CITRA )

#else
	return 0;
#endif

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////

void deinitWindow()
{
#ifdef AFX_SUPPORT_GLFW
	glfwDestroyWindow( window );
	glfwTerminate();
#endif
}

