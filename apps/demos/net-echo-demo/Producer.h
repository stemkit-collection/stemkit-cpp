/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _ECHO_PRODUCER_H_
#define _ECHO_PRODUCER_H_

#include <sk/util/Mapper.h>
#include <sk/io/DataInputStream.h>
#include <sk/io/DataOutputStream.h>
#include <sk/rt/Scope.h>

namespace echo {
  class Producer
    : public virtual sk::util::Mapper<const sk::util::String>
  {
    public:
      Producer(sk::io::InputStream& input, sk::io::OutputStream& output);
      virtual ~Producer();

      bool start();
      bool start(const sk::util::Mapper<const sk::util::String>& mapper);

      // sk::util::Object re-implementation.
      const sk::util::Class getClass() const;

    private:
      Producer(const Producer& other);
      Producer& operator = (const Producer& other);

      // sk::util::Mapper implementation.
      const sk::util::String map(const sk::util::String& item) const;

      sk::io::DataInputStream _input;
      sk::io::DataOutputStream _output;
      const sk::rt::Scope _scope;
  };
}

#endif /* _ECHO_PRODUCER_H_ */
