/*  vi: sw=2:
 *  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef SK_UTIL_OBJECT
#define SK_UTIL_OBJECT

#include <inttypes.h>
#include <ostream>

namespace sk {
  namespace util {
    class Class;
    class String;

    /**  The common base class. It provides querying abilities all objects
     *   must provide. A particular object may override the methods to
     *   provide specifics about itself.
     */
    class Object
    {
      public:
        virtual ~Object();

        /// Instantiates another object of the same class as a copy
        /// of itself.
        virtual Object* clone() const;

        /// Returns the object's class.
        virtual const Class getClass() const;

        /// Returns a unique object id.
        virtual uint64_t getId() const;

        /// Returns a string representation of the object. By default, it
        /// returns the object's class and the objects's id.
        virtual const String toString() const;

        /// Returns a string containing human-readable representation of the
        /// object.
        virtual const String inspect() const;

        virtual Object& getObject();
        virtual const Object& getObject() const;

      protected:
        Object();
    };

    std::ostream& operator << (std::ostream& stream, const sk::util::Object& object);

    bool operator<(const sk::util::Object& first, const sk::util::Object& second);
    bool operator>(const sk::util::Object& first, const sk::util::Object& second);
    bool operator==(const sk::util::Object& first, const sk::util::Object& second);
    bool operator!=(const sk::util::Object& first, const sk::util::Object& second);
    bool operator<=(const sk::util::Object& first, const sk::util::Object& second);
    bool operator>=(const sk::util::Object& first, const sk::util::Object& second);
  }
}

#endif
