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
  The whole purpose of this file is as a temporary work around Microsoft
  Visual Studio 2005 C++ compiler problem with covariant return types in 
  a virtual inheritance chain.

  Program ../../../tests/test-covariants.cc clearly demonstrates this bug.
  This works as expected on all other C++ compilers tested, and it should
  indeed according to the C++ Standard.
   
  When compiled with the this command line:
    cl /TP /EHsc /nologo test-covariants.cc

  it produces the following output:
    C:\tmp>test-covariants
    O::O(), this=0012FF58
    FS::FS(), this=[---0012FF4C---], data=<---123456--->
    FS::clone(), this=[---0012FF44---], data=<---4331824--->
    O::O(), this=0044337C
    FS::FS(), this=00443370, data=123456
    FS::~FS(), this=00443370, data=123456
    O::~O(), this=0044337C
    FS::~FS(), this=0012FF4C, data=123456
    O::~O(), this=0012FF58

  Values in square and angle brackets must be equal among themselves. In other
  words, the presented polymorphic method invocation demonstrates incorrect
  value of "this" variable (slightly offset) during the method execution,
  causing incorrent data member access.
#endif

// TODO: Remove this file and all the references when a fix becomes avalable.

#ifndef _SK_UTIL_COVARIANT_H_
#define _SK_UTIL_COVARIANT_H_

#include <sk/util/upcast.cxx>
#include <memory>

namespace sk {
  namespace util {
    template<typename U> U* covariant(sk::util::Object* object) {
      std::auto_ptr<sk::util::Object> holder(object);
      U& result = sk::util::upcast<U>(*object);
      holder.release();

      return &result;
    }
  }
}

#endif /* _SK_UTIL_COVARIANT_H_ */
