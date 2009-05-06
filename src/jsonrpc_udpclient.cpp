/*
 *  JsonRpc-Cpp - JSON-RPC implementation.
 *  Copyright (C) 2008 Sebastien Vincent <sebastien.vincent@cppextrem.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file jsonrpc_udpclient.cpp
 * \brief JSON-RPC UDP client.
 * \author Sebastien Vincent
 */

#include "jsonrpc_udpclient.h"

#include "netstring.h"

#include <cstring>

namespace Json
{

  namespace Rpc
  {

    UdpClient::UdpClient(const std::string& address, uint16_t port) : Client(address, port)
    {
      m_protocol = UDP;
      memset(&m_sockaddr, 0x00, sizeof(struct sockaddr_storage));
      m_sockaddrlen = 0;
    }

    UdpClient::~UdpClient()
    {
    }

    bool UdpClient::Connect()
    {
      struct addrinfo hints;
      struct addrinfo* res = NULL;
      struct addrinfo* p = NULL;
      char service[8];

      if(m_sock > 0)
      {
        return false;
      }

      if(!GetPort() || GetAddress() == "")
      {
        m_sock = -1;
        return false;
      }

      snprintf(service, sizeof(service), "%u", GetPort());
      service[sizeof(service)-1] = 0x00;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = m_protocol == UDP ? SOCK_DGRAM : SOCK_STREAM;
      hints.ai_protocol = m_protocol;
      hints.ai_flags = 0;

      if(getaddrinfo(GetAddress().c_str(), service, &hints, &res) != 0)
      {
        return false;
      }

      for(p = res ; p ; p = p->ai_next)
      {
        m_sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if(m_sock == -1)
        {
          continue;
        }
        
        memcpy(&m_sockaddr, p->ai_addr, p->ai_addrlen);
        m_sockaddrlen = p->ai_addrlen;

        /* ok so now we have a socket bound, break the loop */
        break;
      }
      
      freeaddrinfo(res);
      p = NULL;
      
      if(m_sock > 0)
      {
        return true;
      }
      
      return false;
    }

    ssize_t UdpClient::Send(const std::string& data)
    {
      std::string rep = data;

      /* encoding if any */
      if(GetEncapsulatedFormat() == Json::Rpc::NETSTRING)
      {
        rep = netstring::encode(rep);
      }

      return ::sendto(m_sock, rep.c_str(), rep.length(), 0, (struct sockaddr*)&m_sockaddr, m_sockaddrlen);
    }

    ssize_t UdpClient::Recv(std::string& data)
    {
      char buf[1500];
      ssize_t nb = -1;

      if((nb = ::recvfrom(m_sock, buf, sizeof(buf), 0, NULL, NULL)) == -1)
      {
        return -1;
      }

      data = std::string(buf, nb);

      /* decoding if any */
      if(GetEncapsulatedFormat() == Json::Rpc::NETSTRING)
      {
        data = netstring::decode(data);
      }

      return nb;
    }

  } /* namespace Rpc */

} /* namespace Json */

