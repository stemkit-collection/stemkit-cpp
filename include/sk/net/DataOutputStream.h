/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_NET_DATAOUTPUTSTREAM_H_
#define _SK_NET_DATAOUTPUTSTREAM_H_

#include <sk/io/DataOutputStream.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace net {
    class DataOutputStream
      : public sk::io::DataOutputStream
    {
      public:
        DataOutputStream(sk::io::OutputStream& stream);
        virtual ~DataOutputStream();

        // sk::io::DataOutputStream re-implementation.
        void writeInt(uint32_t value);
        void writeLong(uint64_t value);
        void writeShort(uint16_t value);

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        DataOutputStream(const DataOutputStream& other);
        DataOutputStream& operator = (const DataOutputStream& other);

        bool _bigEndian;
    };
  }
}

#endif /* _SK_NET_DATAOUTPUTSTREAM_H_ */
