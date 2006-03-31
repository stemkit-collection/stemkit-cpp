/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include <sk/cppunit/SingleLineOutputter.h>
#include <cppunit/TestFailure.h>
#include <cppunit/Message.h>
#include <cppunit/Exception.h>

sk::cppunit::SingleLineOutputter::
SingleLineOutputter(CppUnit::TextUi::TestRunner& runner) 
  : CppUnit::CompilerOutputter(&runner.result(), std::cerr, "%p:%l"), _stream(std::cerr) 
{
}

void
sk::cppunit::SingleLineOutputter::
printFailureType(CppUnit::TestFailure* failure) 
{
  _stream  << ": " << (failure->isError() ? "error" : "assertion") << " in";
}

void 
sk::cppunit::SingleLineOutputter::
printFailedTestName(CppUnit::TestFailure* failure) 
{
  _stream  <<  " "  <<  stripNamespace(failure->failedTestName());
} 

void 
sk::cppunit::SingleLineOutputter::
printFailureMessage(CppUnit::TestFailure* failure) 
{
  CppUnit::Exception *thrownException = failure->thrownException();

  CppUnit::Message message = thrownException->message();
  for(int index=0; index < message.detailCount() ;index++) {
    _stream  <<  (index==0 ? " - " : ", ") << message.detailAt(index);
  }
  _stream << std::endl;
}

const std::string 
sk::cppunit::SingleLineOutputter::
stripNamespace(const std::string& name) const 
{
  std::string::size_type index = name.find_last_of(":");
  if(index == std::string::npos) {
    return name;
  }
  return name.substr(index+1) + "()";
}
