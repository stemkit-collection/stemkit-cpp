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

#include <sk/net/DataOutputStream.h>
#include <arpa/inet.h>

static const sk::util::String __className("sk::net::DataOutputStream");

sk::net::DataOutputStream::
DataOutputStream(sk::io::OutputStream& stream)
  : sk::io::DataOutputStream(stream), _bigEndian(1 == htonl(1))
{
}

sk::net::DataOutputStream::
~DataOutputStream()
{
}

sk::io::DataOutput&
sk::net::DataOutputStream::
reuseOrMake(sk::io::OutputStream& stream, sk::util::Holder<sk::io::DataOutput>& holder)
{
  sk::io::DataOutput* object = dynamic_cast<sk::io::DataOutput*>(&stream);
  if(object) {
    holder.set(*object);
  }
  else {
    holder.set(new sk::net::DataOutputStream(stream));
  }
  return holder.get();
}

const sk::util::Class
sk::net::DataOutputStream::
getClass() const
{
  return sk::util::Class(__className);
}

void 
sk::net::DataOutputStream::
writeInt(int value)
{
  sk::io::DataOutputStream::writeInt(htonl(value));
}

void 
sk::net::DataOutputStream::
writeLong(long long value)
{
  uint64_t x = value;

  if(_bigEndian == false) {
    x = ((((uint64_t)htonl(x)) << 32) + htonl(x >> 32));
  }
  sk::io::DataOutputStream::writeLong(x);
}

void 
sk::net::DataOutputStream::
writeShort(short value)
{
  sk::io::DataOutputStream::writeShort(htons(value));
}
