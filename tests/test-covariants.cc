/*  vim: set sw=2:
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <string>
#include <memory>

struct O {
  O() {
    std::cerr << "O::O(), this=" << this << std::endl;
  }
  virtual ~O() {
    std::cerr << "O::~O(), this=" << this << std::endl;
  }
  virtual O* clone() const {
    std::cerr << "O::clone(), this=" << this << std::endl;
    throw std::string("O:clone: Unsupported");
  }
};

struct S : public virtual O {
  virtual S* clone() const = 0;
};

struct FS : public virtual S {
  FS() : _data(123456) {
    std::cerr << "FS::FS(), this=" << this << ", data=" << _data << std::endl;
  }
  ~FS() {
    std::cerr << "FS::~FS(), this=" << this << ", data=" << _data << std::endl;
  }
  FS* clone() const {
    std::cerr << "FS::clone(), this=" << this << ", data=" << _data << std::endl;
    return new FS();
  }

  int _data;
};

int main(int argc, const char* argv[])
{
  FS fdis;
  S& s = fdis;
  std::auto_ptr<O> o(s.clone());

  return 0;
}
