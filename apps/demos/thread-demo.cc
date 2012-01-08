#include <sk/rt/Thread.h>
#include <sk/rt/Mutex.h>
#include <sk/rt/Locker.h>
#include <sk/rt/Time.h>
#include <iostream>

struct Ticker : public virtual sk::rt::Runnable {
  Ticker(sk::rt::Lock& lock)
    : _lock(lock) {}

  void run() {
    while(true) {
      (sk::rt::Locker(_lock), tick());
    }
  }
  void tick() {
    std::cerr << sk::rt::Thread::currentThread().inspect() << std::endl;
    std::cerr << '[' << sk::rt::Time::now().inspect() << ']' << std::endl;
  }
  sk::rt::Lock& _lock;
};

int main(int argc, const char* const argv[])
{
  sk::rt::Mutex mutex;
  sk::rt::Thread t1(new Ticker(mutex));
  sk::rt::Thread t2(new Ticker(mutex));

  t1.start(); t2.start();
  t1.join();  t2.join();
}
