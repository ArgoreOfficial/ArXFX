#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	
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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _TYPES_H