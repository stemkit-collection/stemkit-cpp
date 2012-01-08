/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_CLASSCASTEXCEPTION_H_
#define _SK_UTIL_CLASSCASTEXCEPTION_H_

#include <sk/util/Exception.h>

namespace sk {
  namespace util {
    class ClassCastException
      : public sk::util::Exception
    {
      public:
        ClassCastException(const sk::util::String& sourceName);
        ~ClassCastException() throw();

        const sk::util::String sourceName() const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        sk::util::String _sourceName;
    };
  }
}

#endif /* _SK_UTIL_CLASSCASTEXCEPTION_H_ */
