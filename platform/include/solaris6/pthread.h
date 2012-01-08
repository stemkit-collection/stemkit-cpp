/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _PLATFORM_SOLARIS6_PTHREAD_H_
#define _PLATFORM_SOLARIS6_PTHREAD_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <../include/pthread.h>
#define pthread_mutexattr_settype(mutex, type) (-1)

#if defined(__cplusplus)
}
#endif

#endif /* _PLATFORM_SOLARIS6_PTHREAD_H_ */
