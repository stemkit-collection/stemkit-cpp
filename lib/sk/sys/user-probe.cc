#include <iostream>
#include <sk/sys/User.h>
#include <sk/rt/Scope.h>
#include <sk/rt/logger/Level.h>

int main(int argc, char* argv[])
{
  if(argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " <user> <password>" << std::endl;
    return 2;
  }
  sk::rt::Scope::controller().setLogLevel(sk::rt::logger::Level::DEBUG);
  sk::rt::Scope::controller().setLogPid(true);
  sk::rt::Scope::controller().setLogObject(true);

  bool result = sk::sys::User::find(argv[1]).authenticate(argv[2]);
  std::cerr << "RESULT: " << result << std::endl;

  return 0;
}
