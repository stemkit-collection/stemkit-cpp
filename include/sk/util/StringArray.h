/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_STRINGARRAY_H_
#define _SK_UTIL_STRINGARRAY_H_

#include <sk/util/ArrayList.hxx>
#include <sk/util/String.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace util {
    class StringArray
      : public sk::util::ArrayList<sk::util::String>::Copying
    {
      public:
        StringArray();
        explicit StringArray(const sk::util::String& item);
        explicit StringArray(const char* item);
        StringArray(const sk::util::StringArray& other);
        virtual ~StringArray();

        static const sk::util::StringArray parse(const sk::util::String& specification);
        static const sk::util::StringArray parse(const sk::util::String& specification, const sk::util::String& separator);

        const sk::util::String& first() const;
        const sk::util::String& last() const;
        const sk::util::String pop();
        const sk::util::String shift();
        const sk::util::StringArray slice(int start, int end) const;
        const sk::util::StringArray slice(int end) const;
        const sk::util::StringArray map(const sk::util::Mapper<const sk::util::String>& mapper) const;

        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::Mapper<const sk::util::String>& mapper) const;
        const sk::util::String join(const sk::util::String& prologue, const sk::util::String& separator, const sk::util::String& epilogue, const sk::util::Mapper<const sk::util::String>& mapper) const;
        using sk::util::ArrayList<sk::util::String>::Copying::join;

        sk::util::StringArray operator + (const sk::util::String& item) const;
        sk::util::StringArray operator + (const sk::util::StringArray& other) const;
        sk::util::StringArray& operator << (const sk::util::String& item);

        sk::util::StringArray& operator = (const sk::util::StringArray& other);
        
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;

      private:
        void set(const sk::util::StringArray& other);
    };
  }
}

#endif /* _SK_UTIL_STRINGARRAY_H_ */
