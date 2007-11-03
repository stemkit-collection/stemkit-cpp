
#include <sk/rt/Scope.h>
#include <sk/rt/logger/Level.h>
#include <sk/io/Pty.h>
#include <unistd.h>

int main()
{
  sk::rt::scope::Config& config = sk::rt::Scope::controller().getAggregator().getConfig();
  config.setLogLevel(sk::rt::logger::Level::DEBUG);
  config.setLogPid(true);
  config.setLogTime(true);
  config.setLogObject(true);

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
