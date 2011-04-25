/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_NET_DATAGRAMPACKET_H_
#define _SK_NET_DATAGRAMPACKET_H_

#include <sk/util/Object.h>

namespace sk {
  namespace net {
    class DatagramPacket 
      : public virtual sk::util::Object
    {
      public:
        DatagramPacket();
        virtual ~DatagramPacket();
    
        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;
    
      private:
        DatagramPacket(const DatagramPacket& other);
        DatagramPacket& operator = (const DatagramPacket& other);
    };
  }
}

#endif /* _SK_NET_DATAGRAMPACKET_H_ */
