#pragma once

#include <stdint.h>

#include <arx/strong_type.hpp>

namespace afx {

enum Type
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

enum Result
{
	ARG_SUCESS = 0,
	ARG_ERROR_OUT_OF_MEMORY,
	ARG_ERROR_UNKNOWN
};


typedef arx::strong_type<uint16_t, struct _BufferID>         BufferID;
typedef arx::strong_type<uint16_t, struct _ImageID>          ImageID;
typedef arx::strong_type<uint16_t, struct _CmdBufferID>      CmdBufferID;
typedef arx::strong_type<uint16_t, struct _ShaderProgramID>  ShaderModuleID;
typedef arx::strong_type<uint16_t, struct _ShaderPipelineID> ShaderPipelineID;


}
