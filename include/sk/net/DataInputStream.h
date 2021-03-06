/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_NET_DATAINPUTSTREAM_H_
#define _SK_NET_DATAINPUTSTREAM_H_

#include <sk/io/DataInputStream.h>
#include <sk/util/Holder.hxx>

namespace sk {
  namespace net {
    class DataInputStream
      : public sk::io::DataInputStream
    {
      public:
        DataInputStream(sk::io::InputStream& stream);
        virtual ~DataInputStream();

        // sk::io::DataInputStream re-implementation.
        uint32_t readInt();
        uint64_t readLong();
        uint16_t readShort();

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        DataInputStream(const DataInputStream& other);
        DataInputStream& operator = (const DataInputStream& other);

        bool _bigEndian;
    };
  }
}

#endif /* _SK_NET_DATAINPUTSTREAM_H_ */
