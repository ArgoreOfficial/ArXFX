#include <stdio.h>

#ifdef AFX_PLATFORM_WINDOWS
#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#elif defined(AFX_PLATFORM_3DS)
#include <3ds.h>
#include <citro3d.h>
#endif

#include <afx/Renderer/LowLevel/LowLevelGraphics.h>
#include <afx/Renderer/LowLevel/Stubs/CitraGraphics.h>

#include <afx/Managers/ResourceManager.h>



struct Vertex
{
	float posX;
	float posY;
	float posZ;
	float pad0;

	float colorR;
	float colorG;
	float colorB;
	float pad1;
};

struct ScreenData
{
	int width;
	int height;
};

#ifdef AFX_SUPPORT_GLFW
GLFWwindow* window;
#endif

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
arc::ILowLevelGraphics* g_graphics;

arc::ShaderPipelineID pipelineID;

arc::BufferID vb;
arc::BufferID screenDataBuffer;

ScreenData screenData;

// function definitions ///////////////////////////////////////////////////////////////

int initWindow();
void deinitWindow();

///////////////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <fstream>

struct ShaderAsset : public arc::iAsset
{
public:
	arc::ShaderModuleID moduleID;
};

template<>
ShaderAsset* arc::ResourceManager::_loadImpl<ShaderAsset, arc::ShaderModuleType>( const std::string& _path, arc::ShaderModuleType _type )
{
	std::ifstream file{ _path };

	if ( !file.is_open() )
		return nullptr;

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string str = buffer.str();

	arc::ShaderProgramDesc desc{};
	desc.type = _type;
	desc.source = str.c_str();
	
	ShaderAsset* asset = new ShaderAsset();
	g_graphics->createProgram( &desc, &asset->moduleID );

	return asset;
}

///////////////////////////////////////////////////////////////////////////////////////

void initBuffers()
{
	Vertex vertices[ 3 ] = {
		{ -0.5f, -0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f, 1.0f },
		{  0.0f,  0.5f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f, 1.0f }
	};

	vb = g_graphics->createBuffer( arc::BufferType::kDYNAMIC, arc::BufferUsage::kDYNAMIC_DRAW, sizeof( vertices ) );
	g_graphics->bufferSubData( vb, vertices, sizeof( vertices ), 0 );

	screenDataBuffer = g_graphics->createBuffer( arc::BufferType::kDYNAMIC, arc::BufferUsage::kDYNAMIC_DRAW, sizeof( ScreenData ) );
}

template <typename _Ty>
_Ty swap_endian( _Ty u )
{
	union
	{
		_Ty u;
		unsigned char u8[ sizeof( _Ty ) ];
	} source, dest;

	source.u = u;

	for ( size_t k = 0; k < sizeof( _Ty ); k++ )
		dest.u8[ k ] = source.u8[ sizeof( _Ty ) - k - 1 ];

	return dest.u;
}
#ifdef AFX_PLATFORM_3DS
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

	if ( !initWindow() ) 
		return 1;

	uint32_t frameNumber = 0;
#ifdef AFX_PLATFORM_WINDOWS
	g_graphics = arc::ILowLevelGraphics::alloc( "OpenGL" );
#elif defined( AFX_PLATFORM_3DS )
	
	// https://stackoverflow.com/questions/60794102/why-is-an-inline-static-variable-of-a-template-class-not-initialized
	g_graphics = new arc::CitraGraphics();

	if( g_graphics == nullptr ) // until we have proper debugging on 3ds
		while ( true ) { }
#endif

	g_graphics->init();

	printf( "Renderer: %s\n", g_graphics->name().c_str() );

#ifdef AFX_PLATFORM_WINDOWS
	arc::CmdBuffer* cmdBuffer = g_graphics->createCmdBuffer();


	arc::ResourceManager resourceManager{};
	
	
	ShaderAsset* vertShader = resourceManager.load<ShaderAsset>( "../../test_vert.glsl", arc::ShaderModuleType::kVERTEX );
	ShaderAsset* fragShader = resourceManager.load<ShaderAsset>( "../../test_frag.glsl", arc::ShaderModuleType::kFRAGMENT );

	//afx::VertexAttrib attribs[] = {
	//	{ "aPosition", 3, afx::Type::kFLOAT, false, sizeof( float ) * 3 },
	//	{ "aColor",    3, afx::Type::kFLOAT, false, sizeof( float ) * 3 }
	//};

	//afx::VertexLayout layout;
	//layout.attributes = attribs;
	//layout.numAttributes = 2;
	//layout.stride = sizeof( attribs );

	arc::ShaderPipelineDesc desc;
	desc.vertexProgram   = vertShader->moduleID;
	desc.fragmentProgram = fragShader->moduleID;
	desc.pVertexLayout = nullptr; // &layout;

	g_graphics->createPipeline( &desc, &pipelineID );

	initBuffers();

	g_graphics->bindPipeline( pipelineID );
	g_graphics->bindBufferIndex( vb, 0 );
	g_graphics->bindBufferIndex( screenDataBuffer, 1 );

	while ( !glfwWindowShouldClose( window ) )
	{
		// update screen data buffer
		glfwGetWindowSize( window, &screenData.width, &screenData.height );

		g_graphics->bufferSubData( screenDataBuffer, &screenData, sizeof( ScreenData ), 0 );

		arc::Image m{};
		g_graphics->_cmdBegin( *cmdBuffer );
		
		g_graphics->_cmdViewport( *cmdBuffer, 0, 0, screenData.width, screenData.height );

		float flash = fabs( sin( frameNumber / 60.0f ) );
		g_graphics->_cmdImageClear( *cmdBuffer, m, flash, 0.0f, flash, 1.0f );

		g_graphics->_cmdEnd( *cmdBuffer );
		g_graphics->_cmdSubmit( *cmdBuffer );
		g_graphics->clearDepth( 0.0f, 0.0f, 0.0f, 1.0f );
		
		g_graphics->draw( 0, 3 );

		glfwSwapBuffers( window );
		glfwPollEvents();

		frameNumber++;
	}

	deinitWindow();
#elif defined( AFX_PLATFORM_3DS )


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
#ifdef AFX_PLATFORM_WINDOWS
	if ( !glfwInit() )
		return 0;

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
	glfwWindowHint( GLFW_TRANSPARENT_FRAMEBUFFER, 1 );
	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "ARC", NULL, NULL );

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
#elif defined( AFX_PLATFORM_3DS )
	return 1;
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

