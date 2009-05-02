/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PROPERTYREGISTRY_H_
#define _SK_UTIL_PROPERTYREGISTRY_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/Boolean.h>
#include <sk/util/Processor.h>

namespace sk {
  namespace util {
    class PropertyRegistry 
      : public virtual sk::util::Object
    {
      public:
        virtual const sk::util::String getProperty(const sk::util::String& name) const = 0;
        virtual const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const = 0;
        virtual const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const = 0;
        virtual bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const = 0;
        virtual int getProperty(const sk::util::String& name, int fallback) const = 0;

        virtual int size() const = 0;
        virtual bool hasProperty(const sk::util::String& name) const = 0;
        virtual const sk::util::String dumpProperty(const sk::util::String& name) const = 0;

        virtual void setProperty(const sk::util::String& name, const sk::util::String& value) = 0;
        virtual void setProperty(const sk::util::String& name, const char* value) = 0;
        virtual void setProperty(const sk::util::String& name, const sk::util::Boolean& value) = 0;
        virtual void setProperty(const sk::util::String& name, int value) = 0;

        virtual void deleteProperty(const sk::util::String& name) = 0;
        virtual void parseProperty(const sk::util::String& name) = 0;
        virtual void clear() = 0;

        virtual void forEach(const sk::util::BinaryProcessor<const sk::util::String, const sk::util::String>& processor) const = 0;
    };
  }
}

#endif /* _SK_UTIL_PROPERTYREGISTRY_H_ */
