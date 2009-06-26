/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_INSPECTINGCONVERTER_HXX_
#define _SK_UTIL_INSPECTINGCONVERTER_HXX_

#include <sk/util/Converter.h>

namespace sk {
  namespace util {
    template<typename T>
    class InspectingConverter 
      : public virtual sk::util::Converter<T, sk::util::String>
    {
      public:
        InspectingConverter();
        ~InspectingConverter();
    
        sk::util::String convert(const T& object) const;
    };
  }
}

#endif /* _SK_UTIL_INSPECTINGCONVERTER_HXX_ */
