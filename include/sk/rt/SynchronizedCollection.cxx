/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_SYNCHRONIZEDCOLLECTION_CXX_
#define _SK_RT_SYNCHRONIZEDCOLLECTION_CXX_

#include <sk/rt/SynchronizedCollection.hxx>
#include <sk/util/Hodler.cxx>

template<typename T>
sk::rt::SynchronizedCollection<T>::
SynchronizedCollection(sk::util::Collection<T>& collection)
  : _collectionHolder(collection), _collection(collection)
{
}

template<typename T>
sk::rt::SynchronizedCollection<T>::
SynchronizedCollection(sk::util::Collection<T>* collection)
  : _collectionHolder(collection), _collection(*collection)
{
}

template<typename T>
sk::rt::SynchronizedCollection<T>::
~SynchronizedCollection()
{
}

template<typename T>
T&
sk::rt::SynchronizedCollection<T>::
get(const Selector<T>& selector) const
{
  return (sk::rt::Lock(_mutex), _collection.get(selector));
}

#endif /* _SK_RT_SYNCHRONIZEDCOLLECTION_CXX_ */
