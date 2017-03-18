#include "os.h"
#include "pubfunc.h"
#include <sys/types.h>
#include <sys/timeb.h>
#include "debug_malloc.h"

// 获取随机数，包括iMin和iMax
uint get_rand(uint iMin, uint iMax)
{
	double dr = rand();	// 包含0和RAND_MAX
	double dMax = (uint)RAND_MAX;
	double iF = dr / (dMax + 1);

	uint iCount = (iMax - iMin) + 1;

	double dsub = 1.0f / (double)iCount;

	uint iR = (uint)(iF / dsub);
	if (iR >= iCount)
	{
		// 这种情况应该不会出现，不过防止一下
		iR = iCount - 1;
	}
	return iR + iMin;
}



// 返回当前时间, time:秒，ms:毫秒
void getcurtime(int64 *time, uint *ms)
{
	int64 tsystime = 0;
	uint lms = 1;

#ifdef _WINDOWS

	struct _timeb timebuffer;
	if (_ftime64_s(&timebuffer) == 0)
	{
		tsystime = timebuffer.time;
		lms = timebuffer.millitm;
	}
#else
	struct timeval val;
	gettimeofday(&val, NULL);
	tsystime = val.tv_sec;
	lms = val.tv_usec / 1000;
#endif

	if (time != NULL)
	{
		*time = tsystime;
	}
	if (ms != NULL)
	{
		*ms = lms;
	}
}
// 返回系统运行了多少秒
int64 gethostruntime_sec()
{
#ifdef _WINDOWS
	return gethostruntime_millisec() / 1000;
#else
	struct timespec val;
	clock_gettime(CLOCK_MONOTONIC, &val);
	int64 ret = val.tv_sec;
	return ret;
#endif
}

// 毫秒
int64 gethostruntime_millisec()
{
#ifdef _WINDOWS
	return GetTickCount64();
#else
	struct timespec val;
	clock_gettime(CLOCK_MONOTONIC, &val);
	int64 ret = val.tv_sec * 1000 + val.tv_nsec / (1000 * 1000);
	return ret;
#endif
}

// 微秒
int64 gethostruntime_us()
{
#ifdef _WINDOWS
	static LARGE_INTEGER dFrequency = { 0 };
	if (0 == dFrequency.QuadPart)
	{
		QueryPerformanceFrequency(&dFrequency);
	}
	LARGE_INTEGER cur;
	QueryPerformanceCounter(&cur);
	double time = ((double)cur.QuadPart) / ((double)dFrequency.QuadPart);
	return (int64)(time * 1000 * 1000);
#else
	struct timespec val;
	clock_gettime(CLOCK_MONOTONIC, &val);
	int64 ret = val.tv_sec * 1000 * 1000 + val.tv_nsec / 1000;
	return ret;
#endif
}

// 纳秒
int64 gethostruntime_nanosec()
{
#ifdef _WINDOWS
	static LARGE_INTEGER dFrequency = { 0 };
	if (0 == dFrequency.QuadPart)
	{
		QueryPerformanceFrequency(&dFrequency);
	}
	LARGE_INTEGER cur;
	QueryPerformanceCounter(&cur);
	double time = (((double)cur.QuadPart)*1000.0) / ((double)dFrequency.QuadPart);
	return (int64)(time * 1000 * 1000);
#else
	struct timespec val;
	clock_gettime(CLOCK_MONOTONIC, &val);
	int64 ret = val.tv_sec * 1000 * 1000 * 1000 + val.tv_nsec;
	return ret;
#endif
}

char * trim(char * pszStr)
{
	size_t iLen = strlen(pszStr);
	size_t iBuflen = iLen + 1;

	// 去年后面的空格
	size_t iNewLen = 0;
	size_t i;
	for (i = iLen - 1; i >= 0; --i)
	{
		char c = pszStr[i];
		if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
		{
			iNewLen = i + 1;
			break;
		}
	}
	pszStr[iNewLen] = '\0';

	size_t iCur = 0;
	for (i = 0; i<iNewLen; ++i)
	{
		char c = pszStr[i];
		if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
		{
			iCur = i;
			break;
		}
	}
	if (iCur > 0)
	{
		StringCbCopy(pszStr, iBuflen, pszStr + iCur);
	}
	return pszStr;
}

bool get_line(const char *pdata, int datalen, int *prolen, char *out_buf, int out_buflen) {
	int pro = *prolen;
	if (pro >= datalen)
	{
		return false;
	}
	out_buf[0] = 0;

	// 去掉前面的换行符
	while (pro < datalen)
	{
		if ('\n' == pdata[pro] || '\r' == pdata[pro])
		{
			++pro;
			continue;
		}
		break;
	}
	int cur = pro;
	// 查找换行符,为了找到一行
	while (cur < datalen)
	{
		if ('\n' == pdata[cur] || '\r' == pdata[cur])
		{
			break;
		}
		cur++;
	}
	// 把一行数据复制到buf中
	if (cur > pro)
	{
		int curlen = cur - pro;
		int iCopyLen = min(curlen, out_buflen - 1);
		memcpy(out_buf, pdata + pro, iCopyLen*sizeof(char));
		out_buf[iCopyLen] = '\0';

		cur++;
		pro = cur;
	}
	*prolen = pro;
	return true;
}

struct split_list {
	char **str;
	int size;
	int bufsize;
};
static void _split_resize(struct split_list *list, int newsize) {
	int unit = sizeof(char*);
	char ** n = malloc(newsize*unit);
	memcpy(n, list->str, list->size*unit);
	free(list->str);
	list->str = n;
	list->bufsize = newsize;
}
static void _splist_add(struct split_list *list, const char *pstr, size_t len) {
	if (list->size >= list->bufsize) {
		_split_resize(list, list->bufsize * 2);
	}
	char *n = malloc(len + 1);
	memcpy(n, pstr, len);
	n[len] = 0;
	list->str[list->size] = n;
	++list->size;
}
struct split_list * split_string(const char* in, int sep) {
	
	struct split_list *list = malloc(sizeof(*list));
	list->size = 0;
	list->str = NULL;
	_split_resize(list, 32);

	while (*in)
	{
		const char* next = strchr(in, sep);
		if (next)
		{
			int len = (int)(next - in);
			_splist_add(list, in, len);
			in = next + 1;
		}
		else
		{
			_splist_add(list, in, strlen(in));
			break;
		}
	}
	if (*in == 0)
	{
		// ",,"这个时候，最后有一个空的
		_splist_add(list, "", 1);
	}
	return list;
}
int split_get_size(struct split_list *list) {
	return list->size;
}
const char *split_get(struct split_list *list, int index) {
	if (index < 0 || index >= list->size) {
		return NULL;
	}
	return list->str[index];
}
void split_free(struct split_list *list) {
	int i;
	for (i = 0; i < list->size; ++i) {
		free(list->str[i]);
	}
	free(list->str);
	list->str = NULL;
	list->size = 0;
	free(list);
}

#ifdef _WINDOWS
#else

char *_strdup(const char *s) {
	int len = strlen(s);
	char *str = malloc(len+1);
	memcpy(str, s, len);
	str[len] = 0;
	return str;
}

#endif