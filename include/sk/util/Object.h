/*  Copyright (c) 2005, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef SK_UTIL_OBJECT
#define SK_UTIL_OBJECT

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

        // Returns a reference to itself.
        virtual Object& self();
        virtual const Object& self() const;

	/// Returns the object's class.
	virtual const Class getClass() const;

	/// Returns a unique object id.
	virtual long long getId() const;

	/// Returns a string representation of the object. By default, it
	/// returns the object's class and the objects's id.
	virtual const String toString() const;

	/// Returns a string containing human-readable representation of the
	/// object.
	virtual const String inspect() const;

      protected:
	Object();
    };
  };
};

#endif
