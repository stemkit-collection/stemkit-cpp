/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _TEST_SPAWNER_H_
#define _TEST_SPAWNER_H_

#include <sk/util/Object.h>

namespace test {
  class Spawner 
    : public virtual sk::util::Object
  {
    public:
      Spawner(int argc, const char* argv[]);
      virtual ~Spawner();

      void start();
  
      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;
  
    private:
      Spawner(const Spawner& other);
      Spawner& operator = (const Spawner& other);

      void perform();
  };
}

#endif /* _TEST_SPAWNER_H_ */
