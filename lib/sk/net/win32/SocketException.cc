/*  vim: sw=2:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/Strings.h>
#include <sk/net/SocketException.h>

#include <winsock2.h>
#include <ws2tcpip.h>

sk::net::SocketException::
SocketException(const sk::util::String& message)
  : sk::rt::SystemException(message, WSAGetLastError())
{
}

sk::net::SocketException::
SocketException(const sk::util::String& message, const sk::util::Strings& details)
  : sk::rt::SystemException(message, details, WSAGetLastError())
{
}
