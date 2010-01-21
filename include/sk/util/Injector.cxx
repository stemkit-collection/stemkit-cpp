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

#include <sk/util/Injector.hxx>
#include <sk/util/UnsupportedOperationException.hxx>

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

template<typename F, typename F>
struct sk::util::Injector<F, T>::Processor : public virtual sk::util::Processor<F> {
  Processor(bool& skip, T& memo, const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<T>& reducer)
    : _skip(skip), _memo(memo), _mapper(mapper), _reducer(reducer) {}

  void process(F& object) const {
    if(_skip == false) {
      _memo = _reducer(_memo, object, _mapper);
    }
    _skip = false;
  }

  bool& _skip;
  T& _memo;
  const sk::util::Mapper<F, T>& _mapper;
  const sk::util::Recuder<T>& _reducer;
};

template<typename F, typename T>
const T
sk::util::Injector<F, T>::
inject(const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<T>& reducer)
{
  if(_list.isEmpty() == true) {
    return T(mapper.map(F()));
  }
  bool skip = true;
  T memo = mapper.map(_list.get(0));
  _list.forEach(Processor(skip, memo, mapper, reducer));

  return memo;
}

template<typename F, typename T>
T&
sk::util::Injector<F, T>::
inject(T& memo, const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<T>& reducer)
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
inject(const T& initial, const sk::util::Mapper<F, T>& mapper, const sk::util::Reducer<T>& reducer)
{
  if(_list.isEmpty() == true) {
    return memo;
  }
  T memo(initial);
  bool skip = false;
  _list.forEach(Processor(skip, memo, mapper, reducer));

  return memo;
}

template<typename F, typename T>
T 
sk::util::Injector<F, T>::
map(F& object) const
{
  throw sk::util::UnsupportedOperationException(SK_METHOD);
}

#endif /* _SK_UTIL_INJECTOR_CXX_ */
