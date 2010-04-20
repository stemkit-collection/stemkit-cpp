/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_CAPPEDSTRINGS_H_
#define _SK_UTIL_CAPPEDSTRINGS_H_

#include <sk/util/Strings.h>

namespace sk {
  namespace util {
    class CappedStrings 
      : public sk::util::Strings
    {
      public:
        CappedStrings();
        CappedStrings(int cap);
        virtual ~CappedStrings();

        bool add(const sk::util::String& item);
        bool add(sk::util::String& item);

        void addFirst(const sk::util::String& item);
        void addFirst(sk::util::String& item);

        void addLast(const sk::util::String& item);
        void addLast(sk::util::String& item);

        void add(int index, const sk::util::String& item);
        void add(int index, sk::util::String& item);

        void set(int index, const sk::util::String& item);
        void set(int index, sk::util::String& item);

        int maxItemSize() const;
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        const sk::util::String ensureCap(const sk::util::String& item);
        
        int _cap;
    };
  }
}

#endif /* _SK_UTIL_CAPPEDSTRINGS_H_ */
