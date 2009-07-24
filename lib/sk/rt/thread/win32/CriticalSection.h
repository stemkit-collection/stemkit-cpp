/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_WIN32_CRITICALSECTION_H_
#define _SK_RT_THREAD_WIN32_CRITICALSECTION_H_

#include <sk/rt/thread/abstract/Mutex.h>
#include <sk/rt/Scope.h>
#include <windows.h>

namespace sk {
  namespace rt {
    namespace thread {
      namespace win32 {
        class CriticalSection 
          : public virtual sk::rt::thread::abstract::Mutex
        {
          public:
            CriticalSection();
            virtual ~CriticalSection();

            void setDepth(int depth);
            void setErrorCheck(bool state);
        
            // sk::rt::thread::abstract::Mutex implementation
            void lock();
            void unlock();
            bool tryLock();
            void reset();
            bool hasEnterCount() const;
            int getEnterCount() const;

            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            CriticalSection(const CriticalSection& other);
            CriticalSection& operator = (const CriticalSection& other);

            void cleanup();
            bool ensureDepth(bool raise);

            int _depth;
            bool _errorCheck;
            sk::rt::Scope _scope;
            CRITICAL_SECTION _section;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_WIN32_CRITICALSECTION_H_ */
