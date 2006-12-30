/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_CPPUNIT_SOURCEPATH_
#define _SK_CPPUNIT_SOURCEPATH_

#include <sk/util/Object.h>
#include <sk/util/String.h>

namespace sk {
  namespace cppunit {
    class SourcePath
      : public virtual sk::util::Object 
    {
      public:
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

        static void setBase(const sk::util::String& path);
        static const sk::util::String make(const sk::util::String& file);
        
      private:
        SourcePath();
        virtual ~SourcePath();
        
        SourcePath(const SourcePath& other);
        SourcePath& operator = (const SourcePath& other);

        static sk::util::String _base;
    };
  }
}

#endif /* _SK_CPPUNIT_SOURCEPATH_ */
