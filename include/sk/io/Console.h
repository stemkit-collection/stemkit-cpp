/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_IO_CONSOLE_H_
#define _SK_IO_CONSOLE_H_

#include <sk/util/Object.h>
#include <sk/util/Holder.hxx>
#include <sk/io/InputStream.h>
#include <sk/io/OutputStream.h>

namespace sk {
  namespace io {
    class Console
      : public virtual sk::util::Object
    {
      public:
        Console();
        virtual ~Console();

        void close();
        sk::io::InputStream& inputStream() const ;
        sk::io::OutputStream& outputStream() const ;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      private:
        Console(const Console& other);
        Console& operator = (const Console& other);

        struct Data;
        sk::util::Holder<Data> _dataHolder;
        Data& _data;
    };
  }
}

#endif /* _SK_IO_CONSOLE_H_ */
