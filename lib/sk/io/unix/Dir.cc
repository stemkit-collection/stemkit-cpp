/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>
#include <sk/util/MappingProcessor.cxx>
#include <sk/util/SelectingProcessor.cxx>
#include <sk/util/MissingResourceException.h>
#include <sk/io/ClosedChannelException.h>
#include <sk/rt/SystemException.h>
#include <sk/io/mapper/PathnameToFileInfo.h>
#include <sk/io/selector/Directory.h>
#include <sk/io/selector/RegularFile.h>

#include <sk/io/Dir.h>
#include <sk/io/FileInfo.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <vector>

struct sk::io::Dir::Data : public virtual sk::util::Object {
  DIR* handle;
};

void
sk::io::Dir::
init()
{
  _dataHolder.set(new Data);

  sk::util::String name = _path.toString();
  DIR* handle = ::opendir(name.getChars());
  if(handle == 0) {
    throw sk::util::MissingResourceException("directory " + _path.inspect());
  }
  _dataHolder.get().handle = handle;
}

void
sk::io::Dir::
close()
{
  DIR** handle = &_dataHolder.get().handle;
  if(*handle != 0) {
    ::closedir(*handle);
    *handle = 0;
  }
}

void 
sk::io::Dir::
forEachEntry(const sk::util::Processor<const sk::util::Pathname>& processor) const
{
  DIR* handle = _dataHolder.get().handle;
  if(handle == 0) {
    throw sk::io::ClosedChannelException();
  }
  ::rewinddir(handle);

  // In the following code readdir() is used instead of readdir_r() as the
  // latter is not fully compatible on all platforms (AIX in particular).
  // Besides, on AIX readdir_r() returns with error with no errno set under
  // certain conditions. It is not thread-safe now.
  //
  while(true) {
    errno = 0;
    struct dirent* result = ::readdir(handle);
    if(result == 0) {
      if(errno == 0) {
        break;
      }
      throw sk::rt::SystemException("readdir_r()");
    }
    const char* name = result->d_name;
    if(name[0] == '.') {
      if(name[1] == 0) {
        continue;
      }
      if(name[1] == '.') {
        if(name[2] == 0) {
          continue;
        }
      }
    }
    processor.process(_path.join(name));
  }
}

void 
sk::io::Dir::
change(const sk::util::String& path)
{
  if(::chdir(path.getChars()) != 0) {
    throw sk::rt::SystemException("chdir");
  }
}

void 
sk::io::Dir::
make(const sk::util::String& path)
{
  if(::mkdir(path.getChars(), 0777) != 0) {
    throw sk::rt::SystemException("mkdir");
  }
}

const sk::util::Pathname 
sk::io::Dir::
current()
{
  std::vector<char> buffer(1024, 0);
  while(::getcwd(&buffer.front(), buffer.size()) == 0) {
    if(errno != ERANGE) {
      throw sk::rt::SystemException("getcwd");
    }
    buffer.resize(buffer.size() + 1024, 0);
  }
  return sk::util::String(&buffer.front());
}

void 
sk::io::Dir::
unlink(const sk::util::String& path)
{
  if(::rmdir(path.getChars()) != 0) {
    throw sk::rt::SystemException("mkdir");
  }
}
