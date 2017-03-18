#pragma once

#ifdef _WINDOWS
#include <crtdbg.h>

#ifdef _DEBUG

	#define malloc(sz) _malloc_dbg(sz, _NORMAL_BLOCK, __FILE__, __LINE__)
	#define realloc(p, sz) _realloc_dbg(p, sz, _NORMAL_BLOCK, __FILE__, __LINE__)
	#define free(p) _free_dbg(p, _NORMAL_BLOCK)

#define _RegDebugNew()											\
	{															\
		int iflag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);		\
		iflag |= _CRTDBG_LEAK_CHECK_DF;							\
		_CrtSetDbgFlag(iflag);									\
	}
#else

	#define _RegDebugNew()

#endif // _DEBUG
#else
#define _RegDebugNew()
#endif // _WINDOWS

