/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_INSPECT_CXX_
#define _SK_UTIL_INSPECT_CXX_

#include <sstream>
#include <sk/util/StringArray.h>

template<typename T>
const sk::util::String 
sk::util::inspect(const T* data) 
{
  if(data == 0) {
    return "<null>";
  }
  std::stringstream stream;
  stream << "<p:" << data << '>';

  return stream.str();
}

template<typename T>
const sk::util::String 
sk::util::inspect(T* data) 
{
  const T* const_data = data;
  return sk::util::inspect(const_data);
}

template<typename T>
const sk::util::String 
sk::util::inspect(const T& data) 
{
  std::stringstream stream;
  stream << data;

  return stream.str();
}

template<typename T> 
const sk::util::String 
sk::util::inspect(const std::vector<T>& container) 
{
  if(container.empty() == true) {
    return "[]";
  }
  sk::util::StringArray depot;
  int index = 0;
  for(typename std::vector<T>::const_iterator iterator = container.begin(); iterator != container.end(); ++iterator) {
    depot << sk::util::String::valueOf(index++) + "=" + sk::util::inspect(*iterator);
  }
  return "[" + sk::util::String::valueOf(container.size()) + ": " + depot.join(", ") + " ]";
}

#endif /* _SK_UTIL_INSPECT_CXX_ */
