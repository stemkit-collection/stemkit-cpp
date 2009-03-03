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
 *  @par
 *
 *  <center>
 *  <em>
 *  by Gennady Bystritsky (bystr@mac.com)
 *  </em>
 *  </center>
 *  
 *  @par
 *
 *  This package provides various facilities helping to build C++ applications 
 *  from scratch. Its API design was greatly inspired by standard Java class 
 *  library, especialy collection framework (@java_api_link{util}) and streams 
 *  (@java_api_link{io}). Its implementation, on the other hand, uses
 *  available C++ facilities like STL and standard IO libraries, often
 *  complicated, verbose or contrived to be used in their pure forms.
 *  @further_details{stl_issues}.
 *
 *  The API and implementation of stemkit-cpp is based upon a set of 
 *  principles, following which has been proven to produce high quality, 
 *  easy to debug code. They also help in greatly reducing possibilities 
 *  of memory leaks. Those principles are:
 *    -# Using pure virtual C++ protocol classes as interfaces, implemented by 
 *       <em>public virtual</em> inheritance. @further_details{interfaces}.
 *    -# Avoiding multiple inheritance by all means other than interface
 *       implementation (no more than one non-virtual inheritance).
 *       @further_details{multiple_inheritance}.
 *    -# All classes inherit (<em>public virtual</em>) from sk::util::Object, thus
 *       having a set of guaranteed properties and capabilities (object id, clone, 
 *       inspect, etc.) @further_details{common_base}.
 *    -# Copy constructors and @c operator=() private by default, otherwise 
 *       only when proven necessary.
 *    -# Methods and method parameters (references) must be declared const by 
 *       default, non-const only if really necessary.
 *    -# Passing pointers means passing objects' ownership. Otherwise,
 *       object copies or references must be passed. 
 *       @further_details{pointers_vs_references}.
 *    -# Getting a pointer is immediatelly followed by placing it in a 
 *       managing container (like sk::util::Holder, sk::util::ArrayList, 
 *       @c std::auto_ptr, @c boost::shared_ptr, etc.).
 *  
 *  <dl>
 *    <dt>The functionality is split into the following main namespaces:
 *    <dd>
 *      <dl>
 *        <dt>sk::util
 *        <dd>
 *          Provides collection framework. Plus utility classes for basic types.
 *      
 *        <dt>sk::io
 *        <dd>
 *          Provides stream classes.
 *      
 *        <dt>sk::net
 *        <dd>
 *          Provides network communication classes.
 *          @todo 
 *            Introduce classes Socket, ServerSocket, etc. (as defined in
 *            @java_api_link{net}).
 *      
 *        <dt>sk::rt
 *        <dd>
 *          Provides runtime support. This includes:
 *            - Scope centered logging and configuration 
 *            - Configuration files lookup and XML parsing
 *            - Thread management and synchronization
 *            - Synchronized wrappers for sk::util containers
 *            - @todo Object disposal with notification 
 *      
 *        <dt>sk::sys
 *        <dd>
 *          Provides OS integration support.
 *      
 *        <dt>sk::cppunit
 *        <dd>
 *          Provides useful extensions for @cppunit_link{CppUnit} unit testing 
 *          framework. Like assertions of strings specified in any manner, with 
 *          persentation of "inspected" content in diagnostics.
 *      </dl>
 *  </dl>
 *
*/

/**
 *  @page common_base sk::util::Object as the root of a class hierarchy
 *
 *  @todo Provide content
*/

/**
 *  @page pointers_vs_references References vs. pointers
 *
 *  @todo Provide content
*/

/**
 *  @page interfaces Denoting interfaces in C++
 *
 *  @todo Provide content
*/

/**
 *  @page multiple_inheritance Multiple inheritance woes
 *
 *  @todo Provide content
*/

/**
 *  @page stl_issues Direct STL use issues
 *
 *  @todo Provide content
*/
