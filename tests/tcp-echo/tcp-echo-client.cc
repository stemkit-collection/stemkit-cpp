/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>

#include <sk/sys/StreamPortal.h>
#include <sk/sys/Process.h>
#include <sk/io/FileDescriptorStream.h>
#include <sk/io/FileDescriptorInputStream.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/io/FileDescriptorOutputStream.h>

int main(int argc, const char* argv[])
{
  sk::sys::StreamPortal& portal = sk::sys::Process::streamPortal();
  sk::io::FileDescriptorStream stream = portal.getStream(0);

  sk::io::FileDescriptorInputStream inputStream(stream.getFileDescriptor());
  sk::io::FileDescriptorOutputStream outputStream(stream.getFileDescriptor());
  sk::io::DataInputStream dataInput(inputStream);
  sk::io::DataOutputStream dataOutput(outputStream);

  while(true) {
    sk::util::String line = dataInput.readLine();
    dataOutput.writeChars("GOT: " + line);
  }
}
