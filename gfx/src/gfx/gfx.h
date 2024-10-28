#pragma once

#if defined( GFX_STACK_ALLOCATED_OBJECTS ) && defined( GFX_HEAP_ALLOCATED_OBJECTS )
#error defining GFX_STACK_ALLOCATED_OBJECTS and GFX_HEAP_ALLOCATED_OBJECTS is not allowed
#endif

#include "gfx_types.h"
#include "gfx_funcdefs.h"

#include "framework/GPUBuffer.h"
#include "framework/Program.h"
#include "framework/Pipeline.h"