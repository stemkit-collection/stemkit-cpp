/*  vim: set sw=2:
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <string>
#include <memory>

struct Object {
  Object() {
    std::cerr << "Object::Object(), this=" << this << std::endl;
  }
  virtual ~Object() {
    std::cerr << "Object::~Object(), this=" << this << std::endl;
  }
  virtual Object* clone() const {
    std::cerr << "Object::clone(), this=" << this << std::endl;
    throw std::string("Object:clone: Unsupported");
  }
};

struct Base : public virtual Object {
  virtual Base* clone() const = 0;
};

struct Derrived : public virtual Base {
  Derrived() : _data(123456) {
    std::cerr << "Derrived::Derrived(), this=" << this << ", data=" << _data << std::endl;
  }
  ~Derrived() {
    std::cerr << "Derrived::~Derrived(), this=" << this << ", data=" << _data << std::endl;
  }
  Derrived* clone() const {
    std::cerr << "Derrived::clone(), this=" << this << ", data=" << _data << std::endl;
    return new Derrived();
  }

  int _data;
};

int main(int argc, const char* argv[])
{
  Derrived fdis;
  Base& s = fdis;
  std::auto_ptr<Object> o(s.clone());

  return 0;
}
