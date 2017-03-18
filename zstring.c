#include "zstring.h"

bool StringCbCopy(char * pszDest, size_t cbDest, const char * pszSrc)
{
	if (cbDest < 1)
		return true;

	int iCount = 0;
	while( (iCount<(cbDest-1)) && (*pszDest = *pszSrc) )
	{		
		++pszDest;
		++pszSrc;
		++iCount;		
	}
	*pszDest = 0;
	return true;
}

#ifndef _WINDOWS

bool strcpy_s(char *pszDst, int iDstBufLen, const char *pszSrc)
{
	return StringCbCopy(pszDst, iDstBufLen, pszSrc);
}

bool strcat_s(char *pszDst, int iDstBufLen, const char *pszSrc)
{
	int iLen = strlen(pszDst);
	return strcpy_s(pszDst+iLen, iDstBufLen-iLen, pszSrc);
}


#endif
