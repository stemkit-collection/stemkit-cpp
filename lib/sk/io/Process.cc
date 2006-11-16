/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/UnsupportedOperationException.h>

#include <sk/io/Process.h>
#include <sk/io/Pipe.h>

#include <unistd.h>

sk::io::Process::
Process(const sk::io::StandardStreamProvider& streamProvider, const sk::util::StringArray& cmdline)
{
}

sk::io::Process::
Process(const sk::util::StringArray& cmdline)
{
}

sk::io::Process::
~Process()
{
}

const sk::util::Class
sk::io::Process::
getClass() const
{
  return sk::util::Class("sk::io::Process");
}

sk::io::Pipe&
sk::io::Process::
getStdin() const 
{
  throw sk::util::UnsupportedOperationException("getStdin()");
}

sk::io::Pipe&
sk::io::Process::
getStdout() const
{
  throw sk::util::UnsupportedOperationException("getStdout()");
}

sk::io::Pipe&
sk::io::Process::
getStderr() const
{
  throw sk::util::UnsupportedOperationException("getStderr()");
}

void 
sk::io::Process::
exec(const sk::util::String& command, const std::vector<char*>& args)
{
  ::execvp(command.getChars(), &args[0]);
}
