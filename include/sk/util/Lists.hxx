/*  vim: set sw=2:
 *  Copyright (c) 2010, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_UTIL_LISTS_HXX_
#define _SK_UTIL_LISTS_HXX_

#include <sk/util/Processor.h>
#include <sk/util/String.h>

namespace sk {
  namespace util {
    template<typename T, typename Policy>
    class Lists 
    {
      public:
        class SlotInspector 
          : public virtual sk::util::Processor<const typename Policy::slot_t> 
        {
          public:
            SlotInspector(sk::util::String& depot, int& index);

            inline void operator()(const typename Policy::const_slot_storage_t& storage) const;
            void process(const typename Policy::slot_t& slot) const;

            const sk::util::String collect() const;

          private:
            sk::util::String& _depot;
            int& _index;
        };
    };
  }
}

template<typename T, typename Policy>
sk::util::Lists<T, Policy>::SlotInspector::
SlotInspector(sk::util::String& depot, int& index)
  : _depot(depot), _index(index) 
{
  _index = 0;
}

template<typename T, typename Policy>
inline void 
sk::util::Lists<T, Policy>::SlotInspector::
operator()(const typename Policy::const_slot_storage_t& storage) const 
{
  if(_index != 0) {
    _depot += ", ";
  }
  _depot += (sk::util::String::valueOf(_index++) + Policy::inspectSlot(storage));
}

template<typename T, typename Policy>
void 
sk::util::Lists<T, Policy>::SlotInspector::
process(const typename Policy::slot_t& slot) const 
{
  (*this)(&slot);
}

template<typename T, typename Policy>
const sk::util::String
sk::util::Lists<T, Policy>::SlotInspector::
collect() const
{
  if(_index == 0) {
    return "[]";
  }
  return "[" + sk::util::String::valueOf(_index) + ": " + _depot + " ]";
}

#endif /* _SK_UTIL_LISTS_HXX_ */
