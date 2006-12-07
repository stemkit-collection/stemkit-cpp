/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/BufferedInputStream.h>
#include <sk/io/EOFException.h>
#include <iostream>

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream), _size(1024)
{
}

sk::io::BufferedInputStream::
BufferedInputStream(sk::io::InputStream& stream, int size)
  : DelegatingInputStream(stream), _size(std::max(0, size))
{
}

sk::io::BufferedInputStream::
~BufferedInputStream()
{
}

const sk::util::Class
sk::io::BufferedInputStream::
getClass() const
{
  return sk::util::Class("sk::io::BufferedInputStream");
}

int
sk::io::BufferedInputStream::
read(char* buffer, int offset, int size)
{
  if(size <= 0) {
    return 0;
  }
  try {
    std::vector<char> depot(_size, 0);

    while(_container.size() < size) {
      int n = filterReadEvents(DelegatingInputStream::read(&depot[0], 0, _size));
      _container.insert(_container.end(), depot.begin(), depot.begin() + n);
    }
  }
  catch(const sk::io::EOFException& excepion) {}

  if(_container.isEmpty() == true) {
    return filterReadEvents(0);
  }
  int outstanding = std::min(_container.size(), size);

  std::copy(_container.begin(), _container.begin() + outstanding, buffer + offset);
  _container.erase(_container.begin(), _container.begin() + outstanding);

  return outstanding;
}
