/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_INJECTOR_CXX_
#define _SK_UTIL_INJECTOR_CXX_

#include <sk/util/Class.h>
#include <sk/util/Injector.hxx>
#include <sk/util/mapper/Coercing.hxx>
#include <sk/util/UnsupportedOperationException.h>

template<typename F, typename T>
sk::util::Injector<F, T>::
Injector(const sk::util::List<F>& list)
  : _list(list)
{
}

template<typename F, typename T>
sk::util::Injector<F, T>::
~Injector()
{
}

template<typename F, typename T>
const sk::util::Class
sk::util::Injector<F, T>::
getClass() const
{
  return sk::util::Class("sk::util::Injector");
}

template<typename F, typename T>
struct sk::util::Injector<F, T>::Processor : public virtual sk::util::Processor<const F> {
  Processor(bool& skip, T& memo, const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer)
    : _skip(skip), _memo(memo), _mapper(mapper), _reducer(reducer) {}

  void process(const F& object) const {
    if(_skip == false) {
      _memo = _reducer.reduce(_memo, object, _mapper);
    }
    _skip = false;
  }

  bool& _skip;
  T& _memo;
  const sk::util::Mapper<const F, const T>& _mapper;
  const sk::util::Reducer<F, T>& _reducer;
};

template<typename F, typename T>
const T
sk::util::Injector<F, T>::
inject(const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const
{
  if(_list.isEmpty() == true) {
    return T();
  }
  bool skip = true;
  T memo = mapper.map(_list.get(0));
  _list.forEach(Processor(skip, memo, mapper, reducer));

  return memo;
}

template<typename F, typename T>
const T
sk::util::Injector<F, T>::
inject(const sk::util::Reducer<F, T>& reducer) const
{
  if(_list.isEmpty() == true) {
    return T();
  }
  bool skip = true;
  T memo(_list.get(0));
  _list.forEach(Processor(skip, memo, sk::util::mapper::Coercing<const F, const T>(), reducer));

  return memo;
}

template<typename F, typename T>
T&
sk::util::Injector<F, T>::
inject(T& memo, const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const
{
  if(_list.isEmpty() == true) {
    return memo;
  }
  bool skip = false;
  _list.forEach(Processor(skip, memo, mapper, reducer));

  return memo;
}

template<typename F, typename T>
const T
sk::util::Injector<F, T>::
inject(const T& initial, const sk::util::Mapper<const F, const T>& mapper, const sk::util::Reducer<F, T>& reducer) const
{
  if(_list.isEmpty() == true) {
    return initial;
  }
  T memo(initial);
  bool skip = false;
  _list.forEach(Processor(skip, memo, mapper, reducer));

  return memo;
}

template<typename F, typename T>
inline const T
sk::util::Injector<F, T>::
inject(const T& initial, const sk::util::Reducer<F, T>& reducer) const
{
  return inject(initial, sk::util::mapper::Coercing<const F, const T>(), reducer);
}

template<typename F, typename T>
inline T&
sk::util::Injector<F, T>::
inject(T& memo, const sk::util::Reducer<F, T>& reducer) const
{
  return inject(memo, sk::util::mapper::Coercing<const F, const T>(), reducer);
}

#endif /* _SK_UTIL_INJECTOR_CXX_ */
