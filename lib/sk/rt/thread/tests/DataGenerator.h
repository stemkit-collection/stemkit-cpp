/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_THREAD_TESTS_DATAGENERATOR_H_
#define _SK_RT_THREAD_TESTS_DATAGENERATOR_H_

#include <sk/util/Object.h>
#include <sk/util/ArrayList.hxx>
#include <sk/rt/Thread.h>
#include <vector>

namespace sk {
  namespace rt {
    namespace thread {
      namespace tests {
        class DataGenerator 
          : public virtual sk::util::Object
        {
          public:
            DataGenerator(int workforce, std::vector<int>& target);
            virtual ~DataGenerator();

            void fill(int amount, int runs);
        
            // sk::util::Object re-implementation.
            const sk::util::Class getClass() const;
        
          private:
            DataGenerator(const DataGenerator& other);
            DataGenerator& operator = (const DataGenerator& other);

            int _workforce;
            std::vector<int>& _target;
            sk::util::ArrayList<sk::rt::Thread> _threads;
        };
      }
    }
  }
}

#endif /* _SK_RT_THREAD_TESTS_DATAGENERATOR_H_ */
