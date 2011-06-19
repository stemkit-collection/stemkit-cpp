
#include <iostream>
#include <sk/rt/Scope.h>
#include <sk/io/Pty.h>
#include <unistd.h>
#include <sk/rt/config/CwdUprootLocator.h>

int main()
{
  try {
    sk::rt::Scope::controller().loadXmlConfig(sk::util::Strings("pty"), sk::rt::config::CwdUprootLocator("src/config/probe.xml"));
    sk::rt::Scope scope("main()");

    int uid = getuid();
    int euid = geteuid();

    scope.debug() << "uid=" << uid;
    scope.debug() << "euid=" << euid;

    seteuid(uid);
    scope.debug() << "euid=" << geteuid();

    sk::io::Pty pty;
    scope.notice() << pty.getName();

    seteuid(euid);
    scope.debug() << "euid=" << geteuid();

    return 0;
  }
  catch(const std::exception& exception) {
    std::cerr << "ERROR: " << exception.what() << std::endl;
  }
  return 5;
}
