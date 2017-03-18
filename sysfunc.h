#ifndef SYSFUNC_H
#define SYSFUNC_H

int getcpucount();

int getsyspagesize();

#ifdef _WINDOWS

#define __sync_add_and_fetch InterlockedExchangeAdd
#define __sync_and_and_fetch InterlockedAnd
#define __sync_bool_compare_and_swap(Destination, Comparand, Exchange) (InterlockedCompareExchange(Destination, Exchange, Comparand)==Comparand)

#define __sync_lock_test_and_set(data, value) (InterlockedCompareExchange(data, value, 0)==value)
#define __sync_lock_release(data) InterlockedExchange(data, 0)

#define localtime_r(t, tm) localtime_s(tm, t)

#else


#endif

#endif