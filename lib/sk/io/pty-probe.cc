
#include <sk/rt/Logger.h>
#include <sk/rt/logger/Level.h>
#include <sk/io/Pty.h>
#include <unistd.h>

int main()
{
  sk::rt::Logger::controller().setLevel(sk::rt::logger::Level::DEBUG);
  sk::rt::Logger::controller().setShowPid(true);
  sk::rt::Logger::controller().setShowTime(true);
  sk::rt::Logger::controller().setShowObject(true);

  sk::rt::Logger logger("main()");

  int uid = getuid();
  int euid = geteuid();

  logger.debug() << "uid=" << uid;
  logger.debug() << "euid=" << euid;

  seteuid(uid);
  logger.debug() << "euid=" << geteuid();

  sk::io::Pty pty;
  logger.notice() << pty.getName();

  seteuid(euid);
  logger.debug() << "euid=" << geteuid();

  return 0;
}
