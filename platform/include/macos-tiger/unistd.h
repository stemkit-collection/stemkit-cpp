/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _PLATFORM_MACOS_TIGER_UNISTD_
#define _PLATFORM_MACOS_TIGER_UNISTD_

#include <../include/unistd.h>

#define setpgrp() setpgid(0, getpid())

#endif /* _PLATFORM_MACOS_TIGER_UNISTD_ */
