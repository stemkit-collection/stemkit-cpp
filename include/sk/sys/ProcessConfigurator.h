/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_SYS_PROCESSCONFIGURATOR_H_
#define _SK_SYS_PROCESSCONFIGURATOR_H_

#include <sk/util/Object.h>
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

namespace sk {
  namespace sys {
    class ProcessConfigurator 
      : public virtual sk::util::Object
    {
      public:
        virtual void setEnvironment(const sk::util::String& name, const sk::util::String& value) = 0;
        virtual void setInputStream(sk::io::InputStream& stream) = 0;
        virtual void setOutputStream(sk::io::OutputStream& stream) = 0;
        virtual void setErrorOutputStream(sk::io::OutputStream& stream) = 0;
        virtual void addStream(sk::io::Stream& stream) = 0;
    };
  }
}

#endif /* _SK_SYS_PROCESSCONFIGURATOR_H_ */
