#include "thread_lock.h"
#ifdef _WINDOWS
#else
#include <pthread.h>
#endif

struct thread_lock {
#ifdef WIN32
	CRITICAL_SECTION	lock;
#else
	pthread_mutex_t		lock;
#endif
};

struct thread_lock *thread_lock_create(bool recursive) {
	struct thread_lock *lock = malloc(sizeof(*lock));
#ifdef _WINDOWS
	InitializeCriticalSection(&lock->lock);
#else
	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_PRIVATE);
	if (recursive) {		
		pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
	}
	pthread_mutex_init(&lock->lock, &mattr);
	pthread_mutexattr_destroy(&mattr);
#endif
	return lock;
}

void thread_lock_release(struct thread_lock *lock) {
	if (NULL == lock) {
		return ;
	}
#ifdef _WINDOWS
	DeleteCriticalSection(&lock->lock);
#else
	pthread_mutex_destroy(&lock->lock);
#endif
	free(lock);
}

void thread_lock_lock(struct thread_lock *lock) {
#ifdef _WINDOWS
	EnterCriticalSection(&lock->lock);
#else
	pthread_mutex_lock(&lock->lock);
#endif
}

void thread_lock_unlock(struct thread_lock *lock) {
#ifdef _WINDOWS
	LeaveCriticalSection(&lock->lock);
#else
	pthread_mutex_unlock(&lock->lock);
#endif
}

bool thread_lock_trylock(struct thread_lock *lock) {
#ifdef _WINDOWS
	return TryEnterCriticalSection(&lock->lock);
#else
	return pthread_mutex_trylock(&lock->lock) == 0;
#endif
}