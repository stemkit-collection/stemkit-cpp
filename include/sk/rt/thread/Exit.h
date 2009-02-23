/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_THREAD_EXIT_H_
#define _SK_RT_THREAD_EXIT_H_

#include <sk/util/Exception.h>
#include <sk/util/SystemException.h>

namespace sk {
  namespace rt {
    namespace thread {
      class Exit 
        : public sk::util::Exception
      {
        public:
          Exit(int code);
          virtual ~Exit() throw();

          int getCode() const;
      
          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;
      
        private:
          Exit(const Exit& other);
          Exit& operator = (const Exit& other);

          int _code;
      };
    }
  }
}

#endif /* _SK_RT_THREAD_EXIT_H_ */
