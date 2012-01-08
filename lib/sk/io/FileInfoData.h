/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_FILEINFODATA_H_
#define _SK_IO_FILEINFODATA_H_

#include <sk/util/Object.h>
#include <sk/io/FileInfo.h>

#include <sys/stat.h>

struct sk::io::FileInfo::Data : public virtual sk::util::Object {
  struct stat status;
};

#endif /* _SK_IO_FILEINFODATA_H_ */
