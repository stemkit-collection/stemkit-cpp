#include <iostream>
#include <sk/sys/User.h>
#include <sk/rt/Scope.h>
#include <sk/rt/config/CwdUprootLocator.h>
#include <sk/util/Boolean.h>

int main(int argc, char* argv[])
{
  if(argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " <user> <password>" << std::endl;
    return 2;
  }
  try {
    sk::rt::Scope::controller().loadXmlConfig("user", sk::rt::config::CwdUprootLocator("src/config/probe.xml"));

    bool result = sk::sys::User::find(argv[1]).authenticate(argv[2]);
    std::cerr << "RESULT: " << sk::util::Boolean(result) << std::endl;

    return 0;
  }
  catch(const std::exception& exception) {
    std::cerr << "EX: " << exception.what() << std::endl;
  }
  catch(...) {
    std::cerr << "Unknown exception" << std::endl;
  }
  return 5;
}
