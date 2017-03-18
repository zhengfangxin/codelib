#include "thread_api.h"
#include "debug_malloc.h"

thread_id thread_create(thread_func func,void * para)
{
#ifdef _WINDOWS
	thread_id r = (thread_id)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, para, 0, 0);
#else
	thread_id r = 0;
	pthread_create(&r, NULL, (void*(*)(void*))func, para);
#endif

	return r;

}

//睡眠
void thread_sleep(uint millis)
{  
#ifdef _WINDOWS
  Sleep(millis);
#else
  usleep(millis*1000);
#endif
}

//清理线程资源
void thread_clear(thread_id thread)
{
#ifdef _WINDOWS
  CloseHandle(thread);
#else
  //linux下应当是不用的
#endif
}

// 等等线程结束
void thread_wait(thread_id thread, uint itime)
{
#ifdef _WINDOWS
	WaitForSingleObject(thread, itime);
#else
	pthread_join(thread, NULL);
#endif
}
// 线程是否退出
bool thread_is_exit(thread_id thread)
{
#ifdef _WINDOWS
	DWORD dwExit = 0;
	GetExitCodeThread(thread, &dwExit);
	if (STILL_ACTIVE == dwExit)
	{
		return false;
	}
#else
	int iRet = pthread_kill(thread, 0);
	if (iRet == 0)
	{
		return false;
	}
#endif
	return true;
}