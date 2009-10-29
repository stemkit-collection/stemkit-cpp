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
  O() {}
  virtual ~O() {}
};

struct A : public virtual O {
  A(int value) : _value(value) {
    std::cerr << "A::A(int), this=" << this << ", value=" << value << std::endl;
  }

  A(const A& other) : _value(other.getValue()) {
    std::cerr << "A::A(const A&), this=" << this << ", other=" << &other << std::endl;
  }

  ~A() {
    std::cerr << "A::~A(), this=" << this << std::endl;
  }

  A duplicateA() const {
    std::cerr << "A::duplicate()" << std::endl;
    A a(10);
    std::cerr << "A::duplicate() - new A created, returning..." << std::endl;
    return a;
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
  // *FIX* B(const B& other) : A(other.duplicateA().getValue()) {
    std::cerr << "B::B(const B&), this=" << this << ", other=" << &other << std::endl;
  }
  ~B() {
    std::cerr << "B::~B(), this=" << this << std::endl;
  }
};

struct C : public virtual O {
  C() : _bHolder(new B(0)) {
    std::cerr << "C::C(), this=" << this << std::endl;
  }

  C(const C& other) : _bHolder(new B(other.getB())) {
    std::cerr << "C::C(const C&), this=" << this << ", other=" << &other << std::endl;
  }

  ~C() {
    std::cerr << "C::~C(), this=" << this << std::endl;
  }

  B& getB() const {
    return *_bHolder.get();
  };

  std::auto_ptr<B> _bHolder;
};

int main(int /*argc*/, const char* /*argv*/[])
{
  C c;
  B b = c.getB();
}
