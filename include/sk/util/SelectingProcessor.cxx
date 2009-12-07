/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_SELECTINGPROCESSOR_CXX_
#define _SK_UTIL_SELECTINGPROCESSOR_CXX_

#include <sk/util/SelectingProcessor.hxx>

template<typename T>
sk::util::SelectingProcessor<T>::
SelectingProcessor(const sk::util::Processor<T>& processor, const sk::util::Selector<T>& selector)
  : _processor(processor), _selector(selector)
{
}

template<typename T>
sk::util::SelectingProcessor<T>::
~SelectingProcessor()
{
}

template<typename T>
void
sk::util::SelectingProcessor<T>::
process(T& object) const
{
  if(_selector.assess(object) == true) {
    _processor.process(object);
  }
}

#endif /* _SK_UTIL_SELECTINGPROCESSOR_CXX_ */
