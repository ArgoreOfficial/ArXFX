#pragma once

namespace arc {

struct CmdBufferData;

enum class CmdBufferState
{
	kINITIAL,
	kRECORDING,
	kEXECUTABLE,
	kPENDING,
	kINVALID
};

struct CmdBuffer
{
	CmdBufferState state = CmdBufferState::kINVALID;
	CmdBufferData* pData;
};

}
