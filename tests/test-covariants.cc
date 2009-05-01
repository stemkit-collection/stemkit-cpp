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
  FDIS() : _data(123456) {
    std::cerr << "FDIS::FDIS(), " << this << ", data=" << _data << std::endl;
  }
  ~FDIS() {
    std::cerr << "FDIS::~FDIS(), " << this << ", data=" << _data << std::endl;
  }
  FDIS* clone() const {
    std::cerr << "FDIS::clone(), " << this << ", data=" << _data << std::endl;
    return new FDIS();
  }

  int _data;
};

int main(int argc, const char* argv[])
{
  FDIS fdis;
  S& s = fdis;
  std::auto_ptr<O> o(s.clone());

  return 0;
}
