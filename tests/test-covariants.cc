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

class O {
  public:
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

class S : public virtual O {
  public:
    virtual S* clone() const = 0;
};

class IS : public virtual S {
  public:
    virtual IS* clone() const = 0;
};

class AS : public virtual IS {
  public:
    AS() {
      std::cerr << "AS::AS(), " << this << std::endl;
    }

    ~AS() {
      std::cerr << "AS::~AS(), " << this << std::endl;
    }

    AS* clone() const {
      std::cerr << "AS::clone(), " << this << std::endl;
      throw std::string("AS:clone: Unsupported");
    }
};

class FDP : public virtual O {
  public:
    virtual void fdp() = 0;
};


class FDIS : public AS, public virtual FDP {
  public:
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

    void fdp() {}

    int _data;
};

O* f(IS& s);

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

O* f(IS& s) {
  return s.clone();
}
