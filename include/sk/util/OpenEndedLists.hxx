/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_OPENENDEDLISTS_HXX_
#define _SK_UTIL_OPENENDEDLISTS_HXX_

#include <sk/util/Validator.h>

namespace sk {
  namespace util {
    template<typename T, typename Policy, typename Type>
    class OpenEndedLists 
    {
      public:
        static inline void addFirst(typename Type::container_t& container, typename Policy::slot_storage_t storage);
        static inline void addLast(typename Type::container_t& container, typename Policy::slot_storage_t storage);

        static inline void removeFirstGeneric(typename Type::container_t& container);
        static inline void removeFirst(typename Type::container_t& container);
        static inline void removeLast(typename Type::container_t& container);

        static inline T* cutoffFirstGeneric(typename Type::container_t& container);
        static inline T* cutoffFirst(typename Type::container_t& container);
        static inline T* cutoffLast(typename Type::container_t& container);
    };
  }
}

template<typename T, typename Policy, typename Type>
inline void
sk::util::OpenEndedLists<T, Policy, Type>::
addFirst(typename Type::container_t& container, typename Policy::slot_storage_t storage)
{
  container.push_front(storage);
}

template<typename T, typename Policy, typename Type>
inline void
sk::util::OpenEndedLists<T, Policy, Type>::
addLast(typename Type::container_t& container, typename Policy::slot_storage_t storage)
{
  container.push_back(storage);
}

template<typename T, typename Policy, typename Type>
inline void 
sk::util::OpenEndedLists<T, Policy, Type>::
removeFirstGeneric(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  Policy::clearSlot(container.front());
  container.erase(container.begin());
}

template<typename T, typename Policy, typename Type>
inline void 
sk::util::OpenEndedLists<T, Policy, Type>::
removeFirst(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  Policy::clearSlot(container.front());
  container.pop_front();
}

template<typename T, typename Policy, typename Type>
inline void 
sk::util::OpenEndedLists<T, Policy, Type>::
removeLast(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  Policy::clearSlot(container.back());
  container.pop_back();
}

template<typename T, typename Policy, typename Type>
inline T*
sk::util::OpenEndedLists<T, Policy, Type>::
cutoffFirstGeneric(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  T* object = Policy::depriveObject(container.front());
  container.erase(container.begin());

  return object;
}

template<typename T, typename Policy, typename Type>
inline T*
sk::util::OpenEndedLists<T, Policy, Type>::
cutoffFirst(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  T* object = Policy::depriveObject(container.front());
  container.pop_front();

  return object;
}

template<typename T, typename Policy, typename Type>
inline T*
sk::util::OpenEndedLists<T, Policy, Type>::
cutoffLast(typename Type::container_t& container)
{
  sk::util::Validator::ensureNotEmpty(container.size());
  T* object = Policy::depriveObject(container.back());
  container.pop_back();

  return object;
}

#endif /* _SK_UTIL_OPENENDEDLISTS_HXX_ */
