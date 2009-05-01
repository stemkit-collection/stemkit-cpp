/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
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
#include <memory>

struct O {
  O() {
    std::cerr << "O::O(), " << this << std::endl;
  }
  virtual ~O() {
    std::cerr << "O::~O(), " << this << std::endl;
  }
  virtual O* clone() const {
    std::cerr << "O::clone(), " << this << std::endl;
    throw std::string("O:clone: Unsupported");
  }
};

struct S : public virtual O {
  virtual S* clone() const = 0;
};

struct FDIS : public virtual S {
  FDIS() {
    std::cerr << "FDIS::FDIS(), " << this << std::endl;
  }
  ~FDIS() {
    std::cerr << "FDIS::~FDIS(), " << this << std::endl;
  }
  FDIS* clone() const {
    std::cerr << "FDIS::clone(), " << this << std::endl;
    return new FDIS();
  }

  int _data;
};

O* f(S& s);

int main(int argc, const char* argv[])
{
  try {
    FDIS stream;
    std::auto_ptr<O> s(f(stream));
  }
  catch(const std::string& exception) {
    std::cerr << "ERROR: " << exception << std::endl;
  }
  return 0;
}

O* f(S& s) {
  return s.clone();
}
