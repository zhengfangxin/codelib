#ifndef thread_h
#define thread_h

#include "os.h"



#ifdef _WINDOWS
  #define thread_id HANDLE
  #define thread_null ((void*)0)
  typedef int(WINAPI * thread_func)(void *);
#else
  #define thread_id pthread_t
  #define thread_null 0
	typedef void *(*thread_func)(void *);
#endif

//创建线程
thread_id thread_create(thread_func func, void * para);
//睡眠
void thread_sleep(uint millis);
//清理线程资源
void thread_clear(thread_id thread);
// 等等线程结束
void thread_wait(thread_id thread, uint itime);
// 线程是否退出
bool thread_is_exit(thread_id thread);

#endif