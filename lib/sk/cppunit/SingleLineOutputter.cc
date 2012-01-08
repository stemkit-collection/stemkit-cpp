/*  vim: set sw=2:
 *  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
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
  _stream  << ':' << (failure->isError() ? 'E' : 'F') << ':';
}

void
sk::cppunit::SingleLineOutputter::
printFailedTestName(CppUnit::TestFailure* failure)
{
  _stream  <<  " "  <<  stripNamespace(failure->failedTestName());
}

namespace {
  const std::string trim(const std::string item) {
    const std::string whitespace = " \t\r\n\b\f";
    std::string::size_type start = item.find_first_not_of(whitespace);
    if(start != std::string::npos) {
      std::string::size_type end = item.find_last_not_of(whitespace);
      return item.substr(start, end == std::string::npos ? end : end - start + 1);
    }
    return "";
  }

  std::string transform(const std::string& detail) {
    std::string::size_type colon = detail.find_first_of(':');
    if(colon != std::string::npos) {
      std::string intro = trim(detail.substr(0, colon));
      if(intro == "Actual") {
        intro = "got";
      }
      else if(intro == "Expected") {
        intro = "need";
      }
      else {
        return detail;
      }
      return intro + ": " + trim(detail.substr(colon + 1, std::string::npos));
    }
    return detail;
  }
}

void
sk::cppunit::SingleLineOutputter::
printFailureMessage(CppUnit::TestFailure* failure)
{
  CppUnit::Exception *thrownException = failure->thrownException();

  CppUnit::Message message = thrownException->message();
  for(int index=0; index < message.detailCount() ;index++) {
    _stream << (index==0 ? " - " : ", ") << transform(message.detailAt(index));
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
