#include <iostream>
#include <sk/sys/User.h>
#include <sk/rt/Scope.h>
#include <sk/rt/Scope.h>
#include <sk/rt/config/CwdUprootLocator.h>
#include <sk/util/Boolean.h>

int main(int argc, char* argv[])
{
  if(argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " <user> <password>" << std::endl;
    return 2;
  }
  sk::rt::Scope::controller().load(sk::rt::config::CwdUprootLocator("src/config/user-probe.xml"));

  bool result = sk::sys::User::find(argv[1]).authenticate(argv[2]);
  std::cerr << "RESULT: " << sk::util::Boolean(result) << std::endl;

  return 0;
}
