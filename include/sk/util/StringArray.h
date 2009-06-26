/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRINGARRAY_
#define _SK_UTIL_STRINGARRAY_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Processor.h>
#include <sk/util/Converter.h>
#include <deque>

namespace sk {
  namespace util {
    class StringArray
      : public std::deque<sk::util::String>,
        public virtual sk::util::Object 
    {
      public:
        StringArray();
        explicit StringArray(const sk::util::String& item);
        explicit StringArray(const char* item);
        virtual ~StringArray();

        static const sk::util::StringArray parse(const sk::util::String& specification);
        static const sk::util::StringArray parse(const sk::util::String& specification, const sk::util::String& separator);

        int size() const;
        bool isEmpty() const;
        const sk::util::String& get(int index) const;
        const sk::util::String& first() const;
        const sk::util::String& last() const;
        const sk::util::String pop();
        const sk::util::String shift();
        const sk::util::StringArray slice(int number) const;
        const sk::util::StringArray map(const sk::util::Converter<sk::util::String, sk::util::String>& converter) const;
        const sk::util::String join(const sk::util::String& separator) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const;

        sk::util::StringArray operator + (const sk::util::String& item) const;
        sk::util::StringArray operator + (const sk::util::StringArray& other) const;
        void forEach(const sk::util::Processor<const sk::util::String>& processor) const;
        sk::util::StringArray& operator << (const sk::util::String& item);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
    };
  }
}

#endif /* _SK_UTIL_STRINGARRAY_ */
