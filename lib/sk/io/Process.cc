/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>

#include <sk/io/Process.h>

#include <unistd.h>

sk::io::Process::
Process(sk::io::Pipe& pipe)
  : _pipe(pipe), _listener(*this)
{
}

sk::io::Process::
Process(sk::io::Pipe& pipe, sk::io::ProcessListener& listener)
  : _pipe(pipe), _listener(listener)
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

void 
sk::io::Process::
started(io::Process& process)
{
}

void 
sk::io::Process::
finished(io::Process& process)
{
}

void 
sk::io::Process::
exec(const sk::util::String& command, const std::vector<char*>& args)
{
  ::execvp(command.getChars(), &args[0]);
}
