#ifndef _ARG_GFX_GFX_H
#define _ARG_GFX_GFX_H

#if defined( ARG_GFX_STACK_ALLOCATED_OBJECTS ) && defined( ARG_GFX_HEAP_ALLOCATED_OBJECTS )
#error defining ARG_GFX_STACK_ALLOCATED_OBJECTS and ARG_GFX_HEAP_ALLOCATED_OBJECTS is not allowed
#endif

#include <gfx/gfx_types.h>
#include <gfx/gfx_funcdefs.h>

#include <gfx/buffer.h>
#include <gfx/program.h>
#include <gfx/pipeline.h>

#endif