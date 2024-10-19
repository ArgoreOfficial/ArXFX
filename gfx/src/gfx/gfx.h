#pragma once

void ( *gfxClear_f )( unsigned int _mask );
#define gfxClear gfxClear_f