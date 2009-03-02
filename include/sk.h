/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_SK_H_
#define _SK_SK_H_

/**
 *  The top namespace for stemkit-cpp.
*/

namespace sk {
}

#endif /* _SK_SK_H_ */

/**
 *  @mainpage stemkit-cpp - All you need to start off a C++ project.
 *
 *  This package provides various facilities helping to build C++ applications 
 *  from scratch. Its API design was greatly inspired by standard Java class 
 *  library, especialy collection framework (@java_api_link{util}) and streams 
 *  (@java_api_link{io}). Its implementation, on the other hand, uses
 *  available C++ facilities like STL and standard IO libraries, often
 *  complicated, verbose or contrived to be used in their pure forms.
 *
 *  The API and implementation of stemkit-cpp is based upon a set of 
 *  principles, following which has been proven to produce high quality, 
 *  easy to debug code. They also help in greatly reducing possibilities 
 *  of memory leaks. Those principles are:
 *    -# Using pure virtual C++ protocol classes as interfaces, implemented by 
 *       "public virtual" inheritance.
 *    -# Avoiding multiple inheritance by all means other than interface
 *       implementation (no more than one non-virtual inheritance).
 *    -# All classes inherit (public virtual) from sk::util::Object, thus
 *       having a set of guaranteed properties (object id, clone, inspect,
 *       etc.)
 *    -# Copy constructors and operator=() private by default, otherwise only
 *       when proven necessary.
 *    -# Methods and method parameters (references) must be declared const by 
 *       default, non-const only if really necessary.
 *    -# Passing pointers means passing objects' ownership. Otherwise,
 *       object copies or references must be passed.
 *    -# Getting a pointer is immediatelly followed by placing it in a managing
 *       container (like sk::util::Holder, sk::util::ArrayList, std::auto_ptr, 
 *       boost::shared_ptr, etc.).
 *  
 *  The functionality is split into the following main namespaces:
 *
 *  <dl>
 *    <dt>sk::util
 *    <dd>
 *      Provides collection framework. Plus utility classes for basic types.
 *
 *    <dt>sk::io
 *    <dd>
 *      Provides stream classes.
 *
 *    <dt>sk::net
 *    <dd>
 *      Provides network communication classes (currently almost empty).
 *
 *    <dt>sk::rt
 *    <dd>
 *      Provides runtime support. This includes:
 *        - Scope centered logging and configuration 
 *        - Configuration files lookup and XML parsing
 *        - Thread management and synchronization
 *        - Synchronized wrappers for sk::util containers
 *
 *    <dt>sk::sys
 *    <dd>
 *      Provides OS integration support.
 *
 *    <dt>sk::cppunit
 *    <dd>
 *      Provides useful extensions for @cppunit_link{CppUnit} unit testing 
 *      framework. Like assertions of strings specified in any manner, with 
 *      persentation of "ispected" content in diagnostics.
 *  </dl>
*/
