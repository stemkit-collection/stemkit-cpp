/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/io/EOFException.h>

#include "Producer.h"

static const sk::util::String __className("echo::Producer");

echo::Producer::
Producer(sk::io::InputStream& input, sk::io::OutputStream& output)
  : _scope(__className), _input(input), _output(output)
{
}

echo::Producer::
~Producer()
{
}

const sk::util::Class
echo::Producer::
getClass() const
{
  return sk::util::Class(__className);
}

void 
echo::Producer::
start()
{
  start(*this);
}

void 
echo::Producer::
start(const sk::util::Mapper<const sk::util::String>& mapper)
{
  try {
    while(true) {
      _output.writeChars(mapper.map(_input.readLine()));
    }
  }
  catch(const sk::io::EOFException& eof) {}
}

const sk::util::String
echo::Producer::
map(const sk::util::String& item) const 
{
  return item;
}
