/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_REJECTINGPROCESSOR_CXX_
#define _SK_UTIL_REJECTINGPROCESSOR_CXX_

#include <sk/util/RejectingProcessor.hxx>

template<typename T>
sk::util::RejectingProcessor<T>::
RejectingProcessor(const sk::util::Processor<T>& processor, const sk::util::Selector<T>& selector)
  : _processor(processor), _selector(selector)
{
}

template<typename T>
sk::util::RejectingProcessor<T>::
~RejectingProcessor()
{
}

template<typename T>
void
sk::util::RejectingProcessor<T>::
process(T& object) const
{
  if(_selector.assess(object) == false) {
    _processor.process(object);
  }
}

#endif /* _SK_UTIL_REJECTINGPROCESSOR_CXX_ */
