/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _PLATFORM_HPUX_UNISTD_
#define _PLATFORM_HPUX_UNISTD_

#include <../include/unistd.h>

#define seteuid(euid) setreuid(-1, euid)

#endif /* _PLATFORM_HPUX_UNISTD_ */
