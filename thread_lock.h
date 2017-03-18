#ifndef thread_lock_h
#define thread_lock_h

#include "os.h"

struct thread_lock;

struct thread_lock *thread_lock_create(bool recursive);
void thread_lock_release(struct thread_lock *lock);
void thread_lock_lock(struct thread_lock *lock);
void thread_lock_unlock(struct thread_lock *lock);
bool thread_lock_trylock(struct thread_lock *lock);


#endif