#include "sysfunc.h"
#include "os.h"

int getcpucount()
{
	int icpuCount = 1;
#ifdef _WINDOWS
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	icpuCount = si.dwNumberOfProcessors;
#else
	icpuCount = sysconf(_SC_NPROCESSORS_ONLN);
#endif

	return icpuCount;
}

int getsyspagesize()
{
#ifdef _WINDOWS
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwPageSize;
#else
	return getpagesize();
#endif
}