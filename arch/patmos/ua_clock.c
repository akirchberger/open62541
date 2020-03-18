/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2019 (c) Andreas Kirchberger
 */

#ifdef UA_ARCHITECTURE_PATMOS

#include <open62541/types.h>

#define UA_DATETIME_USEC 10LL
#define UA_DATETIME_MSEC (UA_DATETIME_USEC * 1000LL)
#define UA_DATETIME_SEC (UA_DATETIME_MSEC * 1000LL)
#define UA_DATETIME_UNIX_EPOCH (11644473600LL * UA_DATETIME_SEC)

UA_DateTime UA_DateTime_now(void) {
    printf("UA_DateTime_now");
    return UA_DATETIME_UNIX_EPOCH;// + get_cpu_usecs()*60/UA_DATETIME_USEC; //us is 60Hz
}
UA_DateTime UA_DateTime_nowMonotonic(void) {
    printf("UA_DateTime_nowMonotonic");
    return 0;
}
UA_Int64 UA_DateTime_localTimeUtcOffset(void) {
    printf("UA_DateTime_localTimeUtcOffset");
    return 0;
}

#endif /* UA_ARCHITECTURE_PATMOS */
