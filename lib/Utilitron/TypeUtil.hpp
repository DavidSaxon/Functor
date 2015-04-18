#ifndef UTILITRON_TYPEUTIL_H_
#   define UTILITRON_TYPEUTIL_H_

#if defined _WIN32 || defined _WIN64
#   define OS_WINDOWS
#endif

#ifndef OS_WINDOWS
#   include <inttypes.h>
#endif

namespace util {

#ifdef OS_WINDOWS
    typedef __int64 int64;
#else
    typedef int64_t int64;
#endif

} // namespace utill

#endif
