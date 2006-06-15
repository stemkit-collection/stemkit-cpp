/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/AbstractOutputStream.h>

const sk::util::Class
sk::io::AbstractOutputStream::
getClass() const
{
  return sk::util::Class("sk::io::AbstractOutputStream");
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
  return write(&data.front(), offset, data.size()-offset);
}

int 
sk::io::AbstractOutputStream::
write(const std::vector<char>& data)
{
  return write(&data.front(), 0, data.size());
}

int 
sk::io::AbstractOutputStream::
write(char byte)
{
  return write(&byte, 0, 1);
}
