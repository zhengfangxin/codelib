#ifndef zstring_h
#define zstring_h

#include "os.h"

bool StringCbCopy(char * pszDest, size_t cbDest, const char * pszSrc);

#ifndef _WINDOWS

bool strcpy_s(char *pszDst, int iDstBufLen, const char *pszSrc);

char *strncpy_s(char *pDst, int iDstLen, const char *pszSrc, int iCount);

bool strcat_s(char *pszDst, int iDstBufLen, const char *pszSrc);

#else
	
#define strcasecmp _stricmp

#endif

#endif
