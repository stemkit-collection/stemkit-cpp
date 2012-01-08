/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SYNCHRONIZEDLIST_HXX_
#define _SK_RT_SYNCHRONIZEDLIST_HXX_

#include <sk/rt/SynchronizedCollection.hxx>
#include <sk/util/List.hxx>

namespace sk {
  namespace rt {
    template<typename T>
    class SynchronizedList
      : public sk::rt::SynchronizedCollection<T>,
        public virtual sk::util::List<T>
    {
      public:
        SynchronizedList(sk::util::List<T>& list);
        SynchronizedList(sk::util::List<T>* list);
        ~SynchronizedList();

        void process(T& object);

      private:
        SynchronizedList(const SynchronizedList<T>& other);
        SynchronizedList<T>& operator = (const SynchronizedList<T>& other);

        sk::util::List<T>& _list;
    };
  }
}

#endif /* _SK_RT_SYNCHRONIZEDLIST_HXX_ */
