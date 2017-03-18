#ifndef __OS_H__
#define __OS_H__

  #ifdef _WINDOWS
	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include <mswsock.h>
    #include <windows.h>
	#include <shlobj.h>
    #include <winbase.h>
    #include <io.h>
    #include <time.h>
	#include <string.h>
	#include <math.h>
	#include <stdio.h>
	#include <stdbool.h>
	#include <stddef.h>
	#include <assert.h>
	#include <direct.h>

	#pragma warning (error: 4715)	// not all control paths return a value 变为错误
	#pragma warning (error: 4716)	// not all control paths return a value 变为错误
	#pragma warning (error: 4700)	// 使用未初始化的变量

  #else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
    #include <sys/select.h>
    #include <sys/fcntl.h>
    #include <sys/time.h>
    #include <signal.h>
    #include <unistd.h>
    #include <dlfcn.h>
    #include <setjmp.h>
    #include <time.h>
    #include <errno.h>
    #include <stdarg.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <arpa/inet.h>
    #include <ctype.h>
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stddef.h>
    #include <netinet/in.h>
	#include <stdbool.h>
	#include <assert.h>
	
    //opendir()等需要的
    #include <dirent.h>

#endif

#include "typedef.h"
#include "sysfunc.h"
#include <stdint.h>

#endif