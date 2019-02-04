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
#include <sk/util/List.h>
#include <sk/util/String.h>
#include <sk/util/mapper/Stringing.hxx>
#include <sk/util/Injector.cxx>
#include <sk/util/reducer/Join.hxx>

namespace sk {
  namespace util {
    template<typename T, typename Policy>
    class Lists 
    {
      public:
        class SlotInspector;
        class ProcessingSlotInspector;

        static inline const sk::util::String join(const sk::util::List<T>& list, const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper);
        static inline const sk::util::String join(const sk::util::List<T>& list, const sk::util::String& separator);
        static inline const sk::util::String join(const sk::util::List<T>& list);
    };

    template<typename T, typename Policy>
    class Lists<T, Policy>::SlotInspector 
    {
      public:
        SlotInspector(sk::util::String& depot, int& index);

        inline void operator()(const typename Policy::const_slot_storage_t& storage) const;
        inline const sk::util::String collect() const;

      private:
        sk::util::String& _depot;
        int& _index;
    };

    template<typename T, typename Policy>
    class Lists<T, Policy>::ProcessingSlotInspector 
      : public Lists<T, Policy>::SlotInspector,
        public virtual sk::util::Processor<const typename Policy::slot_t>
    {
      public:
        ProcessingSlotInspector();

        void process(const typename Policy::slot_t& slot) const;

      private:
        sk::util::String _depot;
        int _index;
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
inline const sk::util::String
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

template<typename T, typename Policy>
inline const sk::util::String 
sk::util::Lists<T, Policy>::
join(const sk::util::List<T>& list, const sk::util::String& separator, const sk::util::Mapper<const T, const sk::util::String>& mapper)
{
  return sk::util::Injector<T, sk::util::String>(list).inject(mapper, sk::util::reducer::Join<T, sk::util::String>(separator));
}

template<typename T, typename Policy>
inline const sk::util::String 
sk::util::Lists<T, Policy>::
join(const sk::util::List<T>& list, const sk::util::String& separator)
{
  return join(list, separator, sk::util::mapper::Stringing<T>());
}

template<typename T, typename Policy>
inline const sk::util::String 
sk::util::Lists<T, Policy>::
join(const sk::util::List<T>& list)
{
  return join(list, "", sk::util::mapper::Stringing<T>());
}

#endif /* _SK_UTIL_LISTS_HXX_ */
