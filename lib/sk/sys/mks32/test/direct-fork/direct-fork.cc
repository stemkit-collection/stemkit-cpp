/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <nutc.h>
#include <unistd.h>
#include <sys/wait.h>

void with_nutc(char* argv[]);
void with_fork_exec(char* argv[]);

int main(int argc, const char* argv[])
{
  char* arguments[] = { 
    "true.exe", 0 
  };
  char* environment[] = { 
    0
  };

  with_fork_exec(arguments);
  with_nutc(arguments);
}

void with_nutc(char* argv[]) 
{
  std::cerr << "READY: " << argv[0] << std::endl;
  int pid = ::_NutForkExecvp(argv[0], argv);
  std::cerr << "STARTED: " << pid << std::endl;
}

void with_fork_exec(char* argv[]) 
{
  int pid = fork();
  if(pid == 0) {
    std::cerr << "IN CHILD" << std::endl;
    ::execvp(argv[0], argv);
    std::cerr << "EXEC FAILED!!!" << std::endl;
    exit(3);
  }
  int status = 0;
  int result = waitpid(pid, &status, 0);
  std::cerr << "DONE: pid=" << pid << ", result=" << result << ", status=" << status << std::endl;
}
