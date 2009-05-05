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

struct A {
  A(int value) : _value(value) {
    std::cerr << "A::A(int), this=" << this << ", value=" << value << std::endl;
  }

  A(const A& other) : _value(other.getValue()) {
    std::cerr << "A::A(const A&), this=" << this << ", other=" << &other << std::endl;
  }

  virtual ~A() {
    std::cerr << "A::~A(), this=" << this << std::endl;
  }

  A duplicateA() const {
    std::cerr << "A::duplicate()" << std::endl;
    return A(10);
  }

  int getValue() const {
    return _value;
  }

  int _value;
};


struct B : public A {
  B(int value) : A(value) {
    std::cerr << "B::B(int), this=" << this << ", value=" << value << std::endl;
  }

  B(const B& other) : A(other.duplicateA()) {
    std::cerr << "B::B(const B&), this=" << this << ", other=" << &other << std::endl;
  }
  virtual ~B() {
    std::cerr << "B::~B(), this=" << this << std::endl;
  }
};

B& makeB(B& b) {
  std::cerr << "makeB()" << std::endl;
  return b;
}

int main(int argc, const char* argv[])
{
  B s = B(1);
  B b = makeB(s);
}
