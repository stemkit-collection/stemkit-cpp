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
        {
          public:
            SlotInspector(sk::util::String& depot, int& index);

            inline void operator()(const typename Policy::const_slot_storage_t& storage) const;
            const sk::util::String collect() const;

          private:
            sk::util::String& _depot;
            int& _index;
        };

        class ProcessingSlotInspector 
          : public SlotInspector,
            public virtual sk::util::Processor<const typename Policy::slot_t>
        {
          public:
            ProcessingSlotInspector();

            void process(const typename Policy::slot_t& slot) const;

          private:
            sk::util::String _depot;
            int _index;
        };
    };
  }
}

// We have to pass the external data references here because STL algorithms
// make copies of passed functors (instance data would not be propagated back
// otherwise).
//
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
const sk::util::String
sk::util::Lists<T, Policy>::SlotInspector::
collect() const
{
  if(_index == 0) {
    return "[]";
  }
  return "[" + sk::util::String::valueOf(_index) + ": " + _depot + " ]";
}

template<typename T, typename Policy>
sk::util::Lists<T, Policy>::ProcessingSlotInspector::
ProcessingSlotInspector()
  : SlotInspector(_depot, _index)
{
}

template<typename T, typename Policy>
void 
sk::util::Lists<T, Policy>::ProcessingSlotInspector::
process(const typename Policy::slot_t& slot) const 
{
  (*this)(&slot);
}

#endif /* _SK_UTIL_LISTS_HXX_ */
