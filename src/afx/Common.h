#pragma once

#include <stdint.h>

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



}
