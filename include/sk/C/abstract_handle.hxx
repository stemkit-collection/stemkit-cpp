/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_C_ABSTRACT_HANDLE_HXX_
#define _SK_C_ABSTRACT_HANDLE_HXX_

namespace sk {
  namespace C {
    template<class T>
    class abstract_handle
    {
      public:
        abstract_handle(T& object);
        abstract_handle(T* object);
        virtual ~abstract_handle();

        T& get() const;
        
      private:
        abstract_handle(const abstract_handle<T>& other);
        abstract_handle& operator = (const abstract_handle<T>& other);

        const bool _deletable;
        T* _object;
    };
  }
}

#endif /* _SK_C_ABSTRACT_HANDLE_HXX_ */
