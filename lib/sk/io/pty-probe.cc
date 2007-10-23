
#include <sk/rt/Scope.h>
#include <sk/rt/logger/Level.h>
#include <sk/io/Pty.h>
#include <unistd.h>

int main()
{
  sk::rt::Scope::controller().setLevel(sk::rt::logger::Level::DEBUG);
  sk::rt::Scope::controller().setShowPid(true);
  sk::rt::Scope::controller().setShowTime(true);
  sk::rt::Scope::controller().setShowObject(true);

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
