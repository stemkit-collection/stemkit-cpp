/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_PATHNAME_
#define _SK_UTIL_PATHNAME_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    class Pathname
      : public virtual sk::util::Object
    {
      public:
        Pathname(const char* component);
        Pathname(const sk::util::String& component);
        Pathname(const sk::util::String& component, const sk::util::String& defaultExtension);
        virtual ~Pathname();

        bool isEmpty() const;
        bool isAbsolute() const;
        bool isExplicit() const;
        bool isTerminal() const;

        const sk::util::Pathname dirname() const;
        const sk::util::String basename() const;
        const sk::util::String extension() const;
        const sk::util::String location() const;

        const sk::util::Pathname join(const sk::util::Pathname& other) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String toString() const;
        const sk::util::String inspect() const;

        bool operator == (const sk::util::Pathname& other) const;
        bool operator != (const sk::util::Pathname& other) const;

      private:
        void normalize(const sk::util::String& trimmedComponent);

        sk::util::String _path;
        sk::util::String _location;
    };
  }
}

const sk::util::Pathname operator+(const sk::util::Pathname& first, const sk::util::Pathname& second);

#endif /* _SK_UTIL_PATHNAME_ */
