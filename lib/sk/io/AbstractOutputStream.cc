/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/AbstractOutputStream.h>
#include <sk/io/IOException.h>

const sk::util::Class
sk::io::AbstractOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::AbstractOutputStream");
}

sk::io::AbstractOutputStream*
sk::io::AbstractOutputStream::
clone() const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

void 
sk::io::AbstractOutputStream::
flush()
{
}

int 
sk::io::AbstractOutputStream::
write(const std::vector<char>& data, int offset)
{
  if(offset < 0) {
    offset = 0;
  }
  int n = write(&data.front(), offset, data.size()-offset);
  if(n < 0) {
    throw sk::io::IOException("sk::io::AbstractOutputStream::write(vector, offset)");
  }
  return n;
}

int 
sk::io::AbstractOutputStream::
write(const std::vector<char>& data)
{
  return write(data, 0);
}

int 
sk::io::AbstractOutputStream::
write(char byte)
{
  return write(&byte, 0, 1);
}
