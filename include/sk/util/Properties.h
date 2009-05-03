/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_UTIL_PROPERTIES_H_
#define _SK_UTIL_PROPERTIES_H_

#include <sk/util/PropertyRegistry.h>
#include <map>

namespace sk {
  namespace util {
    class Properties 
      : public virtual sk::util::PropertyRegistry
    {
      public:
        Properties();
        Properties(const Properties& other);
        virtual ~Properties();
    
        // sk::util::PropertyRegistry implementation.
        const sk::util::String getProperty(const sk::util::String& name) const;
        const sk::util::String getProperty(const sk::util::String& name, const sk::util::String& fallback) const;
        const sk::util::String getProperty(const sk::util::String& name, const char* fallback) const;
        bool getProperty(const sk::util::String& name, const sk::util::Boolean& fallback) const;
        int getProperty(const sk::util::String& name, int fallback) const;

        // sk::util::PropertyRegistry implementation.
        int size() const;
        bool hasProperty(const sk::util::String& name) const;
        const sk::util::String dumpProperty(const sk::util::String& name) const;

        // sk::util::PropertyRegistry implementation.
        void setProperty(const sk::util::String& name, const sk::util::String& value);
        void setProperty(const sk::util::String& name, const char* value);
        void setProperty(const sk::util::String& name, const sk::util::Boolean& value);
        void setProperty(const sk::util::String& name, int value);

        // sk::util::PropertyRegistry implementation.
        bool deleteProperty(const sk::util::String& name);
        void parseProperty(const sk::util::String& specification);
        void clear();

        // sk::util::PropertyRegistry implementation.
        void forEach(const sk::util::BinaryProcessor<const sk::util::String, const sk::util::String>& processor) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
        const sk::util::String inspect() const;
    
      private:
        Properties& operator = (const Properties& other);
        typedef std::map<sk::util::String, sk::util::String> container;
        container _depot;
    };
  }
}

#endif /* _SK_UTIL_PROPERTIES_H_ */
