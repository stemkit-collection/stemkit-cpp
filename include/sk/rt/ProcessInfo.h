/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_PROCESSINFO_H_
#define _SK_RT_PROCESSINFO_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/rt/Lock.h>

namespace sk {
  namespace rt {
    class ProcessInfo 
      : public virtual sk::util::Object
    {
      public:
        virtual ~ProcessInfo();

        uint64_t pid() const;
        uint64_t virtualMemory() const;
        uint64_t virtualMemory(sk::rt::Lock& lock) const;
        uint64_t residentMemory() const;
        uint64_t residentMemory(sk::rt::Lock& lock) const;

        static void reset();
        static const sk::rt::ProcessInfo& current();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        ProcessInfo();
        ProcessInfo(const ProcessInfo& other);
        ProcessInfo& operator = (const ProcessInfo& other);

        void init();

        uint64_t _pid;

        struct Data;
        sk::util::Holder<Data> _dataHolder;
    };
  }
}

#endif /* _SK_RT_PROCESSINFO_H_ */
