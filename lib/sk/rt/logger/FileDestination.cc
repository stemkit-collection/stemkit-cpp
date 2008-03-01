/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Integer.h>
#include <sk/util/NumberFormatException.h>

#include <logger/FileDestination.h>

sk::rt::logger::FileDestination::
FileDestination(const sk::util::Pathname& pathname)
  : _pathname(pathname), _size(0), _backups(0)
{
}

sk::rt::logger::FileDestination::
~FileDestination()
{
}

const sk::util::Class
sk::rt::logger::FileDestination::
getClass() const
{
  return sk::util::Class("sk::rt::logger::FileDestination");
}

const sk::util::Pathname&
sk::rt::logger::FileDestination::
getPathname() const
{
  return _pathname;
}

void
sk::rt::logger::FileDestination::
setSize(const sk::util::String& specification)
{
  try {
    _size = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
setSize(int size)
{
  _size = size;
}

void
sk::rt::logger::FileDestination::
setBackups(const sk::util::String& specification)
{
  try {
    _backups = sk::util::Integer::parseInt(specification);
  }
  catch(const sk::util::NumberFormatException& exception) {}
}

void
sk::rt::logger::FileDestination::
setBackups(int backups)
{
  _backups = backups;
}

int 
sk::rt::logger::FileDestination::
getSize() const
{
  return _size;
}

int 
sk::rt::logger::FileDestination::
getBackups() const
{
  return _backups;
}
