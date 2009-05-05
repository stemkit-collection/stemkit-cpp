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

struct C {
  C() {
    std::cerr << "C::C(), this=" << this << std::endl;
  }
  C(const C& other) {
    std::cerr << "C::C(const C&), this=" << this << std::endl;
  }
  ~C() {
    std::cerr << "C::~C(), this=" << this << std::endl;
  }
};

struct A {
  A(const C& c) {
    std::cerr << "A::A(const C&), this=" << this << ", c=" << &c << std::endl;
  }
  A(const A& other) {
    std::cerr << "A::A(const A&), this=" << this << std::endl;
  }
  virtual ~A() {
    std::cerr << "A::~A(), this=" << this << std::endl;
  }
};

C maketemp() {
  std::cerr << "maketemp()" << std::endl;
  return C();
}

struct B : public A {
  B() : A(maketemp()) {
    std::cerr << "B::B(), this=" << this << std::endl;
  }
  B(const B& other) : A(other) {
    std::cerr << "B::B(const B&), this=" << this << std::endl;
  }
  virtual ~B() {
    std::cerr << "B::~B(), this=" << this << std::endl;
  }
};

int main(int argc, const char* argv[])
{
  B b;
}
