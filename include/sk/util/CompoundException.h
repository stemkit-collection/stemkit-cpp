/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_COMPOUNDEXCEPTION_H_
#define _SK_UTIL_COMPOUNDEXCEPTION_H_

#include <sk/util/Exception.h>
#include <sk/util/List.h>
#include <sk/util/Holder.hxx>
#include <sk/util/List.h>

namespace sk {
  namespace util {
    class CompoundException
      : public sk::util::Exception
    {
      public:
        CompoundException(const sk::util::List<sk::util::Exception>& exceptions);
        virtual ~CompoundException() throw();

        int size() const;
        const sk::util::Exception& exceptionAt(int index) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        typedef sk::util::List<sk::util::Exception> exception_list_t;
        sk::util::Holder<exception_list_t>::Sharing _listHolder;
        exception_list_t& _list;
    };
  }
}

#endif /* _SK_UTIL_COMPOUNDEXCEPTION_H_ */
