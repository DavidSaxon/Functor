#ifndef UTILITRON_TIMEUTIL_H_
#   define UTILITRON_TIMEUTIL_H_

#include <boost/date_time/date.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "lib/Utilitron/TypeUtil.hpp"

#ifdef OS_WINDOWS
#   include <windows.h>
#else
#   include <unistd.h>
#endif

namespace util {

/************************************\
| Utility functions relating to time |
\************************************/
namespace time {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

//! the number of milliseconds in a second
static const float MS_IN_SEC = 1000.0f;
//! the number of microseconds in a millisecond
static const float US_IN_MS  = 1000.0f;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Causes this thread to sleep for the given number of milliseconds */
inline void sleep( unsigned ms )
{
#ifdef OS_WINDOWS
    Sleep( ms );
#else
    usleep( ms * static_cast<unsigned>( US_IN_MS ) );
#endif
}

/** @return the time passed since the first of January 1970 */
inline boost::posix_time::ptime getEpoch() {

    return boost::posix_time::ptime(boost::gregorian::date(1970, 1, 1));
}

/** @return time passed in milliseconds since epoch */
inline util::int64 getCurrentTime() {

    // epoch
    boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));

    // get the time now
    boost::posix_time::ptime now =
        boost::posix_time::microsec_clock::local_time();
    // get the difference in time since epoch
    boost::posix_time::time_duration diff =
        now - epoch;
    // return the time in milliseconds
    return diff.total_milliseconds();
}

} // namespace time

} // namespace util

#endif
