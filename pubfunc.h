#ifndef PUBFUNC_H
#define PUBFUNC_H

#include "os.h"
#include "zstring.h"
#include "sysfunc.h"
#include "thread_api.h"
#include "file_sys.h"


// 获取随机数，包括iMin和iMax
uint get_rand(uint iMin, uint iMax);

// 返回当前时间, time:秒，ms:毫秒
void getcurtime(int64 *time, uint *ms);

// 返回系统运行了多少秒
int64 gethostruntime_sec();

// 毫秒
int64 gethostruntime_millisec();

// 微秒(在多CPU系统中，两个结果可能不同，所以不要跨线程对比)
int64 gethostruntime_us();

// 纳秒(在多CPU系统中，两个结果可能不同，所以不要跨线程对比)
int64 gethostruntime_nanosec();

// 去年左右两边的空格
char *  trim(char * pszStr);

bool get_line(const char *pdata, int datalen, int *prolen, char *out_buf, int out_buflen);

// 分隔字符串
struct split_list;
struct split_list * split_string(const char* in, int sep);
int split_get_size(struct split_list *list);
const char *split_get(struct split_list *list, int index);
void split_free(struct split_list *list);

#ifdef _WINDOWS
#else

char *_strdup(const char *s);

#endif
#endif