/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SYNCHRONIZEDLIST_CXX_
#define _SK_RT_SYNCHRONIZEDLIST_CXX_

#include <sk/rt/SynchronizedList.hxx>

template<typename T>
sk::rt::SynchronizedList<T>::
SynchronizedList(sk::util::List<T>& list)
  : sk::rt::SynchronizedCollection<T>(list), _list(list)
{
}

template<typename T>
sk::rt::SynchronizedList<T>::
SynchronizedList(sk::util::List<T>* list)
  : sk::rt::SynchronizedCollection<T>(list), _list(*list)
{
}

template<typename T>
sk::rt::SynchronizedList<T>::
~SynchronizedList()
{
}

template<typename T>
void
sk::rt::SynchronizedList<T>::
process(T& object)
{
}

#endif /* _SK_RT_SYNCHRONIZEDLIST_CXX_ */
