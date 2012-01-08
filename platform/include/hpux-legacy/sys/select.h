/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _PLATFORM_HPUX_SELECT_
#define _PLATFORM_HPUX_SELECT_

#include <sys/time.h>

#define seteuid(euid) setreuid(-1, euid)

#endif /* _PLATFORM_HPUX_SELECT_ */
