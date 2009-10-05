/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/Holder.cxx>

#include <sk/net/DataInputStream.h>
#include <arpa/inet.h>

static const sk::util::String __className("sk::net::DataInputStream");

sk::net::DataInputStream::
DataInputStream(sk::io::InputStream& stream)
  : sk::io::DataInputStream(stream), _bigEndian(1 == htonl(1))
{
}

sk::net::DataInputStream::
~DataInputStream()
{
}

sk::io::DataInputStream&
sk::net::DataInputStream::
reuseOrMake(sk::io::InputStream& stream, sk::util::Holder<sk::io::DataInputStream>& _holder)
{
  try {
    _holder.set(sk::util::upcast<sk::io::DataInputStream>(stream));
  }
  catch(const sk::util::ClassCastException& exception) {
    _holder.set(new sk::net::DataInputStream(stream));
  }
  return _holder.get();
}

const sk::util::Class
sk::net::DataInputStream::
getClass() const
{
  return sk::util::Class(__className);
}

int 
sk::net::DataInputStream::
readInt()
{
  return ntohl(sk::io::DataInputStream::readInt());
}

long long 
sk::net::DataInputStream::
readLong()
{
  uint64_t x = sk::io::DataInputStream::readLong();
  if(_bigEndian == false) {
    x = ((((uint64_t)ntohl(x)) << 32) + ntohl(x >> 32));
  }
  return x;
}

short 
sk::net::DataInputStream::
readShort()
{
  return ntohs(sk::io::DataInputStream::readShort());
}
