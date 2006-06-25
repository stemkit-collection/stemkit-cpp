/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Container.h>
#include <sk/util/IndexOutOfBoundsException.h>

#include "MockOutputStream.h"
#include <iostream>

sk::io::test::MockOutputStream::
MockOutputStream()
  : _closeCounter(0), _flushCounter(0)
{
}

sk::io::test::MockOutputStream::
~MockOutputStream()
{
}

const sk::util::Class
sk::io::test::MockOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::test::MockOutputStream");
}

void
sk::io::test::MockOutputStream::
close() 
{ 
  _closeCounter++;
}

int
sk::io::test::MockOutputStream::
closeCounter() const
{ 
  return _closeCounter;
}

void
sk::io::test::MockOutputStream::
flush()
{
  _flushCounter++;
}

int
sk::io::test::MockOutputStream::
flushCounter() const
{
  return _flushCounter;
}

int 
sk::io::test::MockOutputStream::
write(const char* buffer, int offset, int size)
{
  _dataChunks.push_back(sk::util::Container(buffer+offset, size));
  return size;
}

int 
sk::io::test::MockOutputStream::
chunks() const
{
  return _dataChunks.size();
}

namespace {
  struct SizeCollector
  {
    SizeCollector(int& size)
      : _size(size) {}

    void operator()(const sk::util::Container& container) const {
      _size += container.size();
    }
    int& _size;
  };
}

int 
sk::io::test::MockOutputStream::
dataSize() const
{
  int size = 0;
  std::for_each(_dataChunks.begin(), _dataChunks.end(), SizeCollector(size));
  return size;
}

namespace {
  struct Accumulator
  {
    Accumulator(sk::util::Container& container)
      : _container(container) {}

    void operator() (const sk::util::Container& container) const {
      _container += container;
    }
    sk::util::Container& _container;
  };
}

const sk::util::Container
sk::io::test::MockOutputStream::
data() const
{
  sk::util::Container result;
  std::for_each(_dataChunks.begin(), _dataChunks.end(), Accumulator(result));
  return result;
}

const sk::util::Container
sk::io::test::MockOutputStream::
chunk(int index) const
{
  if(index<0 || index>=_dataChunks.size()) {
    throw sk::util::IndexOutOfBoundsException("chunk()");
  }
  return _dataChunks[index];
}
