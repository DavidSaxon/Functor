#ifndef UTILITRON_THREADUTIL_HPP_
#   define UTILITRON_THREADUTIL_HPP_

// TODO: REMOVE
#include <iostream>

#include "lib/Utilitron/TypeUtil.hpp"

#ifdef OS_WINDOWS
#   include <windows.h>
#else
#   include <pthread.h>
#   include <sched.h>
#endif

namespace util {

/****************************************\
| Utility functions relating to threads. |
\****************************************/
namespace thread {

/** Sets the priority of the current thread */
inline void setCurrentPriority( int priority )
{
#ifdef OS_WINDOWS

    // just to be safe this is working...
    if ( priority == 15 )
    {
        priority = THREAD_PRIORITY_TIME_CRITICAL;
    }
    else if ( priority == 0 )
    {
        priority = THREAD_PRIORITY_NORMAL;
    }

    // make the windows system call
    SetThreadPriority( GetCurrentThread(), priority );

#else

    // get the current thread
    pthread_t thisThread = pthread_self();

    // create thread parameters structure
    struct sched_param params;
    params.sched_priority = priority;

    // TODO: this normally fails...
    // set the priority
    pthread_setschedparam( thisThread, SCHED_RR, &params );

#endif
}

} // namespace thread

} // namespace util

#endif
