/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_TEST_PROBE_CXX_
#define _SK_UTIL_TEST_PROBE_CXX_

#include <sk/util/test/Probe.hxx>

template<typename T>
int sk::util::test::Probe<T>::_counter = 0;

template<typename T>
sk::util::test::Probe<T>::
Probe(const T& object)
  : T(object)
{
  _counter++;
}

template<typename T>
sk::util::test::Probe<T>::
Probe(const Probe<T>& other)
  : T(other)
{
  _counter++;
}

template<typename T>
sk::util::test::Probe<T>::
~Probe()
{
  _counter--;
}

template<typename T>
void
sk::util::test::Probe<T>::
resetCounter()
{
  _counter = 0;
}

template<typename T>
int
sk::util::test::Probe<T>::
getCounter()
{
  return _counter;
}

#endif /* _SK_UTIL_TEST_PROBE_CXX_ */
