/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#if 0
  This program demonstrates a problem with linux implementation of
  pthread_mutex when attribute PTHREAD_MUTEX_ERRORCHECK is used. In 
  this case, unlocking in child fails both in direct calls or from 
  pthread_atfork() despite rationale in pthread doc. 

  A bug report for exactly same problem was filed for Linux glibc, 
  available from at http://sourceware.org/ml/glibc-bugs/2006-06/msg00016.html

  Looks like it will not be fixed as a bonehead at redhat.com who got
  this assigned (Ulrich Drepper) refused to admit the problem in a very 
  rude and unprofessional manner.

  Another guy suggested that only pthread_init() may be called on mutex in
  a child process. It works, however according to PTHREAD documentation 
  mutex unlock must work as well, it is even presented in examples.

  The way this file is checked in, it uses pthread_mutex_init() for 
  pthread_atfork() child handler. Replace reset_mutex with unlock_mutex to 
  see the problem on Linux. Works on all other platforms as expected.
#endif

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <errno.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_mutexattr_t mattr;

extern "C" void unlock_mutex() {
  int code;
  std::cerr << ">>> unlock_mutex: " << getpid() << std::endl;
  if((code = pthread_mutex_unlock(&mutex)) != 0) {
    std::cerr << "E: unlock: " << getpid() << ": " << code << ": " << strerror(code) << std::endl;
  }
}

extern "C" void reset_mutex() {
  int code;
  std::cerr << ">>> reset_mutex: " << getpid() << std::endl;
  if((code = pthread_mutex_init(&mutex, &mattr)) != 0) {
    std::cerr << "E: reset: " << getpid() << ": " << code << ": " << strerror(code) << std::endl;
  }
}

int main(int argc, const char* argv[])
{
  int code; 
  if((code = pthread_mutexattr_init(&mattr)) != 0) {
    std::cerr << "E: attr: init: " << code << ": " << strerror(code) << std::endl;
    exit(3);
  }

  if((code=pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_ERRORCHECK)) != 0) {
    std::cerr << "E: attr: type: " << code << ": " << strerror(code) << std::endl;
    exit(3);
  }

  if((code = pthread_mutex_init(&mutex, &mattr)) != 0) {
    std::cerr << "E: init: " << code << ": " << strerror(code) << std::endl;
    exit(3);
  }

  void (*child_handler)() = unlock_mutex;
  if(argc > 1 && std::string("init") == argv[1]) {
    child_handler = reset_mutex;
  }

  if((code = pthread_atfork(0, unlock_mutex, child_handler)) != 0) {
    std::cerr << "E: atfork: " << code << ": " << strerror(code) << std::endl;
    exit(3);
  }

  if((code = pthread_mutex_lock(&mutex)) != 0) {
    std::cerr << "E: lock: " << code << ": " << strerror(code) << std::endl;
    exit(3);
  }
  
  if(fork() == 0) {
  }
  else {
    sleep(1);
  }

  if((code = pthread_mutex_destroy(&mutex)) != 0) {
    std::cerr << "E: destroy: " << getpid() << ": " << code << ": " << strerror(code) << std::endl;
  }
  return 0;
}

