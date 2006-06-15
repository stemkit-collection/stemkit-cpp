/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/DataInputStream.h>

sk::io::DataInputStream::
DataInputStream(sk::io::InputStream& stream)
  : DelegatingInputStream(stream)
{
}

sk::io::DataInputStream::
~DataInputStream()
{
}

const sk::util::Class
sk::io::DataInputStream::
getClass() const
{
  return sk::util::Class("sk::io::DataInputStream");
}

int 
sk::io::DataInputStream::
readInt()
{
  throw sk::util::UnsupportedOperationException("readInt()");
}

long long 
sk::io::DataInputStream::
readLong()
{
  throw sk::util::UnsupportedOperationException("readLong()");
}

short 
sk::io::DataInputStream::
readShort()
{
  throw sk::util::UnsupportedOperationException("readShort()");
}

char 
sk::io::DataInputStream::
readChar()
{
  return getInputStream().read();
}

double 
sk::io::DataInputStream::
readDouble()
{
  throw sk::util::UnsupportedOperationException("readDouble()");
}

float 
sk::io::DataInputStream::
readFloat()
{
  throw sk::util::UnsupportedOperationException("readFloat()");
}

int 
sk::io::DataInputStream::
skipBytes(int number)
{
  return getInputStream().skip(number);
}

const sk::util::String 
sk::io::DataInputStream::
readLine()
{
  throw sk::util::UnsupportedOperationException("readLine()");
}

std::vector<char>& 
sk::io::DataInputStream::
readFully(std::vector<char>& buffer, int number)
{
  throw sk::util::UnsupportedOperationException("readFully()");
}

std::vector<char> 
sk::io::DataInputStream::
readFully(int number)
{
  throw sk::util::UnsupportedOperationException("readFully()");
}
