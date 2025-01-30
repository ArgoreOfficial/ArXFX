#pragma once

#include <stdint.h>

#include <arx/strong_type.hpp>

namespace arc {

enum class Type
{
	kINT,
	kUNSIGNED_INT,
	kSHORT,
	kUNSIGNED_SHORT,
	kLONG,
	kUNSIGNED_LONG,
	kFLOAT,
	kDOUBLE
};

enum class Result
{
	kERROR_UNKNOWN = 0,
	
	kSUCESS = 1,

	kERROR_OUT_OF_MEMORY,
};


typedef arx::strong_type<uint16_t, struct _BufferID>         BufferID;
typedef arx::strong_type<uint16_t, struct _ImageID>          ImageID;
typedef arx::strong_type<uint16_t, struct _CmdBufferID>      CmdBufferID;
typedef arx::strong_type<uint16_t, struct _ShaderProgramID>  ShaderModuleID;
typedef arx::strong_type<uint16_t, struct _ShaderPipelineID> ShaderPipelineID;



#ifdef _MSVC_LANG
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif

}
