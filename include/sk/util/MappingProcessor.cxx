/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_MAPPINGPROCESSOR_CXX_
#define _SK_UTIL_MAPPINGPROCESSOR_CXX_

#include <sk/util/MappingProcessor.hxx>

template<typename F, typename T>
sk::util::MappingProcessor<F, T>::
MappingProcessor(const sk::util::Processor<T>& processor, const sk::util::Mapper<F, T>& mapper)
  : _processor(processor), _mapper(mapper)
{
}

template<typename F, typename T>
sk::util::MappingProcessor<F, T>::
~MappingProcessor()
{
}

template<typename F, typename T>
void
sk::util::MappingProcessor<F, T>::
process(F& object) const
{
  _processor.process(_mapper.map(object));
}

#endif /* _SK_UTIL_MAPPINGPROCESSOR_CXX_ */
