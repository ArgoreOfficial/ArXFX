#ifndef _ARG_GFX_GFX_H
#define _ARG_GFX_GFX_H

#if defined( ARG_GFX_STACK_ALLOCATED_OBJECTS ) && defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
#error defining ARG_GFX_STACK_ALLOCATED_OBJECTS and ARG_GFX_HEAP_ALLOCATED_OBJECTS is not allowed
#endif

#include <gfx/types.h>

#include <gfx/buffer.h>
#include <gfx/program.h>
#include <gfx/pipeline.h>
#include <gfx/vertex_layout.h>

void argGfxViewport( int _x, int _y, int _width, int _height );

void argGfxSetClearColor( float _r, float _g, float _b, float _a );

void argGfxClearRenderTarget( ArgGfxClearMask _mask );

void argGfxSetFillMode( ArgGfxFillMode _mode );

void argGfxDraw( uint32_t _firstVertex, uint32_t _numVertices );

void argGfxDrawIndexed( uint32_t _numIndices );

void argGfxDrawIndexedInstanced( uint32_t _numIndices, uint32_t _numInstances, uint32_t _baseVertex );


#ifdef ARG_GFX_IMP_OPENGL
#include <gfx/impl/gfx_impl_opengl.h>
#endif

#endif