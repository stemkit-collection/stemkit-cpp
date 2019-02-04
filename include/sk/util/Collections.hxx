/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_COLLECTIONS_HXX_
#define _SK_UTIL_COLLECTIONS_HXX_

namespace sk {
  namespace util {
    template<typename T, typename Policy>
    class Collections 
    {
      public:
        static inline typename Policy::slot_storage_t makeStorage(const T& object);
        static inline typename Policy::slot_storage_t makeStorage(T& object);
        static inline typename Policy::slot_storage_t makeStorage(T* object);
    };
  }
}

template<typename T, typename Policy>
inline typename Policy::slot_storage_t
sk::util::Collections<T, Policy>::
makeStorage(const T& object)
{
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  return storage;
}

template<typename T, typename Policy>
inline typename Policy::slot_storage_t
sk::util::Collections<T, Policy>::
makeStorage(T& object)
{
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  return storage;
}

template<typename T, typename Policy>
inline typename Policy::slot_storage_t
sk::util::Collections<T, Policy>::
makeStorage(T* object)
{
  typename Policy::slot_storage_t storage = 0;
  Policy::setObject(storage, object);

  return storage;
}

#endif /* _SK_UTIL_COLLECTIONS_HXX_ */
