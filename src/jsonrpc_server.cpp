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
 * \file jsonrpc_server.cpp
 * \brief JSON-RPC server.
 * \author Sebastien Vincent
 */

#include "jsonrpc_server.h"

#ifndef _WIN32
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <netdb.h>

#else
#include <winsock2.h>
#endif

namespace Json 
{

  namespace Rpc
  {

    Server::Server(const std::string& address, uint16_t port)
    {
      m_sock = -1;
      m_address = address;
      m_port = port;
      SetEncapsulatedFormat(Json::Rpc::RAW);
    }

    Server::~Server()
    {
      ::close(m_sock);
    }

    void Server::SetEncapsulatedFormat(enum EncapsulatedFormat format)
    {
      m_format = format;
    }

    enum EncapsulatedFormat Server::GetEncapsulatedFormat() const
    {
      return m_format;
    }

    int Server::GetSocket() const
    {
      return m_sock;
    }

    std::string Server::GetAddress() const
    {
      return m_address;
    }

    uint16_t Server::GetPort() const
    {
      return m_port;
    }

    bool Server::Bind()
    {
      struct addrinfo hints;
      struct addrinfo* res = NULL;
      struct addrinfo* p = NULL;
      char service[8];

      if(m_sock > 0)
      {
        return false;
      }

      if(!m_port || m_address == "")
      {
        m_sock = -1;
        return false;
      }

      snprintf(service, sizeof(service), "%u", m_port);
      service[sizeof(service)-1] = 0x00;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = m_protocol == UDP ? SOCK_DGRAM : SOCK_STREAM;
      hints.ai_protocol = m_protocol;
      hints.ai_flags = AI_PASSIVE;

      if(getaddrinfo(m_address.c_str(), service, &hints, &res) != 0)
      {
        return false;
      }

      for(p = res ; p ; p = p->ai_next)
      {
        int on = 1;

        m_sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if(m_sock == -1)
        {
          continue;
        }

        setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

        /* accept IPv6 OR IPv4 on the same socket */
        on = 1;
        setsockopt(m_sock, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on));

        if(::bind(m_sock, p->ai_addr, p->ai_addrlen) == -1)
        {
          ::close(m_sock);
          m_sock = -1;
          continue;
        }

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

    void Server::AddMethod(CallbackMethod* method)
    {
      m_jsonHandler.AddMethod(method);
    }

    void Server::DeleteMethod(const std::string& method)
    {
      m_jsonHandler.DeleteMethod(method);
    }

  } /* namespace Rpc */

} /* namespace Json */

