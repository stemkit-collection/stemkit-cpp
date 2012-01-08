/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/io/IOException.h>
#include <sk/io/ByteArrayInputStream.h>
#include <sk/util/IndexOutOfBoundsException.h>
#include <sk/util/Holder.cxx>

#include "MockInputStream.h"

sk::io::test::MockInputStream::
MockInputStream()
  : _closeCounter(0)
{
  setData("");
}

sk::io::test::MockInputStream::
~MockInputStream()
{
}

const sk::util::Class
sk::io::test::MockInputStream::
getClass() const
{
  return sk::util::Class("sk::io::test::MockInputStream");
}

void
sk::io::test::MockInputStream::
close()
{
  _closeCounter++;
}

int
sk::io::test::MockInputStream::
closeCounter() const
{
  return _closeCounter;
}

int
sk::io::test::MockInputStream::
read(char* buffer, int offset, int size)
{
  int n = _streamHolder.getMutable().read(buffer, offset, size);
  _chunks.push_back(sk::util::Container(buffer+offset, n));

  return n;
}

void
sk::io::test::MockInputStream::
setData(const sk::util::Container& container)
{
  _data = container;
  _streamHolder.set(new sk::io::ByteArrayInputStream(_data));
  _chunks.clear();
}

int
sk::io::test::MockInputStream::
chunks() const
{
  return _chunks.size();
}

const sk::util::Container
sk::io::test::MockInputStream::
chunk(int index) const
{
  if(index < 0 || index >= _chunks.size()) {
    throw sk::util::IndexOutOfBoundsException("chunks()");
  }
  return _chunks[index];
}

void
sk::io::test::MockInputStream::
inheritable(bool /*state*/)
{
}
