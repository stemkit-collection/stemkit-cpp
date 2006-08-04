/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_UTIL_ABSTRACT_C_HANDLE_HXX_
#define _SK_UTIL_ABSTRACT_C_HANDLE_HXX_

namespace sk {
  namespace util {
    template<class T>
    class abstract_c_handle
    {
      public:
        abstract_c_handle(T& object);
        abstract_c_handle(T* object);
        virtual ~abstract_c_handle();

        T& get() const;
        
      private:
        abstract_c_handle(const abstract_c_handle<T>& other);
        abstract_c_handle& operator = (const abstract_c_handle<T>& other);

        bool _deletable;
        T* _object;
    };
  }
}

#endif /* _SK_UTIL_ABSTRACT_C_HANDLE_HXX_ */
