/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_C_ABSTRACT_HANDLE_HXX_
#define _SK_C_ABSTRACT_HANDLE_HXX_

#include <sk/C/handle.h>
#include <sk/util/Mapper.h>

namespace sk {
  namespace C {
    template<class T>
    class abstract_handle
      : public sk_c_handle
    {
      public:
        abstract_handle(T& object);
        abstract_handle(const sk::util::Mapper<bool, T*>& mapper);
        virtual ~abstract_handle();

        bool isManaged() const;
        void clear();

        T& get() const;
        T* release();

        template<typename F, typename R>
        R invoke(const sk::util::Mapper<F, R>& mapper) const;
        
      private:
        abstract_handle(const abstract_handle<T>& other);
        abstract_handle& operator = (const abstract_handle<T>& other);

        bool _managed;
        bool _owner;
        T* _object;
    };
  }
}

#endif /* _SK_C_ABSTRACT_HANDLE_HXX_ */
