#ifndef _GFX_H
#define _GFX_H


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <ARG/types.h>

#ifndef ARG_GFX_BACKEND
	#define ARG_GFX_BACKEND 1
	#define ARG_GFX_BACKEND_OPENGL 1 /* default backend */
#endif

#if !defined( ARG_GFX_STACK_ALLOCATED_OBJECTS ) && !defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
	#define ARG_GFX_STACK_ALLOCATED_OBJECTS 1 /* stack allocate by default */
#endif

#if defined( ARG_GFX_STACK_ALLOCATED_OBJECTS ) && defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
	#error defining ARG_GFX_STACK_ALLOCATED_OBJECTS and ARG_GFX_HEAP_ALLOCATED_OBJECTS is not allowed
#endif

#define ARG_OBJECT_HANDLE( _name ) typedef struct _name##_t* _name

ARG_OBJECT_HANDLE( ArgGfxContext );
ARG_OBJECT_HANDLE( ArgGfxProgram );
ARG_OBJECT_HANDLE( ArgGfxPipeline );
ARG_OBJECT_HANDLE( ArgGfxBuffer );

typedef enum ArgResult
{
	ARG_SUCESS = 0,
	ARG_ERROR_OUT_OF_MEMORY,
	ARG_ERROR_UNKNOWN
} ArgResult;

typedef enum ArgGfxBufferType
{
	ARG_GFX_BUFFER_TYPE_NONE = 0,
	ARG_GFX_BUFFER_TYPE_INDEX,
	ARG_GFX_BUFFER_TYPE_VERTEX,
	ARG_GFX_BUFFER_TYPE_UNIFORM,
	ARG_GFX_BUFFER_TYPE_DYNAMIC
} ArgGfxBufferType;

typedef enum ArgGfxBufferUsage
{
	ARG_GFX_BUFFER_USAGE_NONE = 0,
	ARG_GFX_BUFFER_USAGE_STATIC_DRAW,
	ARG_GFX_BUFFER_USAGE_DYNAMIC_DRAW
} ArgGfxBufferUsage;

typedef enum ArgGfxClearMask
{
	ARG_GFX_CLEAR_MASK_COLOR = 1,
	ARG_GFX_CLEAR_MASK_DEPTH = 2
} ArgGfxClearMask;

typedef enum ArgGfxFillMode
{
	ARG_GFX_FILL_MODE_SOLID = 0,
	ARG_GFX_FILL_MODE_WIREFRAME,
	ARG_GFX_FILL_MODE_POINTS
} ArgGfxFillMode;

typedef enum ArgGfxShaderProgramType
{
	ARG_GFX_SHADER_TYPE_VERTEX = 0,
	ARG_GFX_SHADER_TYPE_FRAGMENT
} ArgGfxShaderProgramType;

typedef struct ArgGfxBufferDesc
{
	ArgGfxBufferType type;
	ArgGfxBufferUsage usage;
	int32_t size;
} ArgGfxBufferDesc;

typedef struct ArgGfxProgramDesc
{
	ArgGfxShaderProgramType type;
	const char* source;
} ArgGfxProgramDesc;

typedef struct ArgGfxVertexAttrib
{
	const char* name;
	unsigned int componentCount;
	ArgType type;
	uint8_t normalized;
	unsigned int size;
} ArgGfxVertexAttrib;

typedef struct ArgGfxVertexLayout
{
	ArgGfxVertexAttrib* attributes;
	unsigned int numAttributes;
	unsigned int stride;
} ArgGfxVertexLayout;

typedef struct ArgGfxPipelineDesc
{
	ArgGfxProgram vertexProgram;
	ArgGfxProgram fragmentProgram;
	ArgGfxVertexLayout* pVertexLayout;
} ArgGfxPipelineDesc;

ArgResult argGfxInit();

ArgResult argGfxCreateContext(
	ArgGfxContext* _pContext );

ArgResult argGfxViewport(
	ArgGfxContext _ctx, 
	int _x, 
	int _y, 
	int _width, 
	int _height );

ArgResult argGfxSetClearColor(
	ArgGfxContext _ctx, 
	float _r, 
	float _g, 
	float _b, 
	float _a );

ArgResult argGfxClearRenderTarget(
	ArgGfxContext _ctx, 
	ArgGfxClearMask _mask );

ArgResult argGfxSetFillMode(
	ArgGfxContext _ctx, 
	ArgGfxFillMode _mode );

ArgResult argGfxDraw(
	ArgGfxContext _ctx, 
	uint32_t _firstVertex, 
	uint32_t _numVertices );

ArgResult argGfxDrawIndexed(
	ArgGfxContext _ctx, 
	uint32_t _numIndices );

ArgResult argGfxDrawIndexedInstanced(
	ArgGfxContext _ctx, 
	uint32_t _numIndices, 
	uint32_t _numInstances, 
	uint32_t _baseVertex );

ArgResult argGfxCreateProgram(
	ArgGfxContext _ctx,  
	ArgGfxProgramDesc* _desc,
	ArgGfxProgram* _pProgram );

ArgResult argGfxDestroyProgram(
	ArgGfxContext _ctx, 
	ArgGfxProgram _program );

ArgResult argGfxCreatePipeline(
	ArgGfxContext _ctx,  
	ArgGfxPipelineDesc* _desc,
	ArgGfxPipeline* _pPipeline );

ArgResult argGfxDestroyPipeline(
	ArgGfxContext _ctx, 
	ArgGfxPipeline _pipeline );

ArgResult argGfxBindPipeline(
	ArgGfxContext _ctx, 
	ArgGfxPipeline _pipeline );

ArgResult argGfxBindVertexLayout(
	ArgGfxContext _ctx, 
	ArgGfxVertexLayout* _pVertexLayout );

ArgResult argGfxCreateBuffer(
	ArgGfxContext _ctx, 
	ArgGfxBufferDesc* _desc,
	ArgGfxBuffer* _pBuffer );

ArgResult argGfxDestroyBuffer(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _buffer );

ArgResult argGfxBindBuffer(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _buffer );

ArgResult argGfxBindBufferIndex(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _buffer, 
	int32_t _bindingIndex );

ArgResult argGfxBufferData(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _buffer, 
	void* _pData, 
	size_t _size );

ArgResult argGfxBufferSubData(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _buffer, 
	void* _pData, 
	size_t _size, 
	size_t _base );

ArgResult argGfxCopyBufferSubData(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _readBuffer, 
	ArgGfxBuffer _writeBuffer, 
	size_t _readOffset, 
	size_t _writeOffset, 
	size_t _size );

ArgResult argGfxBindVertexBuffer(
	ArgGfxContext _ctx, 
	ArgGfxBuffer _vertexPullBuffer );


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // _GFX_H