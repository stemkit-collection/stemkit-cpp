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

#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>

void start(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
  try {
    sk::rt::Scope::controller().loadXmlConfig(
      sk::rt::config::InlineLocator("\n\
        <scope name='app'>\n\
          <log destination='file' eol='windows' level='debug' show-object='true' show-pid='true' show-time='true'>\n\
            <file name='tcp-echo.log' />\n\
          </log>\n\
          \n\
          <scope name='thread-exception-handler'>\n\
            <property name='abort-on-exception' value='true' />\n\
          </scope>\n\
          \n\
          <scope name='sk::rt::thread::pthreads::Mutex'>\n\
            <property name='perform-error-check' value='true' />\n\
          </scope>\n\
          \n\
        </scope>\n\
      ")
    );
    start(argc, argv);
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
}

void start(int argc, const char* argv[]) {
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
