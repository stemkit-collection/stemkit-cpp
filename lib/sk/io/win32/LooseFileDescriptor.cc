/*  vi: sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/LooseFileDescriptor.h>
#include <sk/rt/SystemException.h>

#include <windows.h>
#include <io.h>

void 
sk::io::LooseFileDescriptor::
inheritable(bool state)
{
  /*
  HANDLE handle = reinterpret_cast<HANDLE>(_get_osfhandle(getFileNumber()));
  int flag = (state==true ? HANDLE_FLAG_INHERIT : 0);

  if(SetHandleInformation(handle, HANDLE_FLAG_INHERIT, flag) == 0) {
    throw sk::rt::SystemException("SetHandleInformation");
  }
  */
}

