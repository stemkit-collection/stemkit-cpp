/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_STANDARDCONTAINER_HXX_
#define _SK_UTIL_STANDARDCONTAINER_HXX_

namespace sk {
  namespace util {
    template<typename T, typename Policy, typename Type>
    class StandardContainer 
    {
      public:
        StandardContainer();
        ~StandardContainer();
    
        void process(T& object);
    
      private:
        StandardContainer(const StandardContainer<T, Policy, Type>& other);
        StandardContainer<T, Policy, Type>& operator = (const StandardContainer<T, Policy, Type>& other);

        typedef typename Type::item_t item_t;
        typedef typename Type::container_t container_t;

        container_t _container;
    };
  }
}

#endif /* _SK_UTIL_STANDARDCONTAINER_HXX_ */
