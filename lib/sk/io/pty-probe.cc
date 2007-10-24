
#include <sk/rt/Scope.h>
#include <sk/rt/logger/Level.h>
#include <sk/io/Pty.h>
#include <unistd.h>

int main()
{
  sk::rt::Scope::controller().setLogLevel(sk::rt::logger::Level::DEBUG);
  sk::rt::Scope::controller().setLogPid(true);
  sk::rt::Scope::controller().setLogTime(true);
  sk::rt::Scope::controller().setLogObject(true);

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
