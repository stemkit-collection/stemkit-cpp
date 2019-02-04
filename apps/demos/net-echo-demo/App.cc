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
#include <sk/util/Integer.h>
#include <sk/util/IllegalArgumentException.h>

#include "App.h"

static const sk::util::String __className("echo::App");

namespace {
  const sk::net::InetSocketAddress figureEndpoint(const sk::util::Pathname& program, const int argc, const char* const argv[]) {
    switch(argc) {
      case 2: return sk::net::InetSocketAddress(sk::util::Integer::parseInt(argv[1]));
      case 3: return sk::net::InetSocketAddress(argv[1], sk::util::Integer::parseInt(argv[2]));
    }
    throw sk::util::IllegalArgumentException("USAGE: " + program.basename() + " <address> <port>");
  }
}

echo::App::
App(const sk::util::String& name, const int argc, const char* const argv[])
  : _scope(name), _program(argv[0]), _endpoint(figureEndpoint(_program, argc, argv))
{
}

echo::App::
~App()
{
}

const sk::util::Class
echo::App::
getClass() const
{
  return sk::util::Class(__className);
}

const sk::net::InetSocketAddress&
echo::App::
endpoint() const
{
  return _endpoint;
}

const sk::util::Pathname&
echo::App::
program() const 
{
  return _program;
}

const sk::rt::Scope&
echo::App::
scope() const 
{
  return _scope;
}
