#ifndef _ARG_TYPES_H
#define _ARG_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum ArgType
{
	ARG_INT,
	ARG_UNSIGNED_INT,
	ARG_SHORT,
	ARG_UNSIGNED_SHORT,
	ARG_LONG,
	ARG_UNSIGNED_LONG,
	ARG_FLOAT,
	ARG_DOUBLE
} ArgType;

typedef uint32_t ArgHandle;

#endif