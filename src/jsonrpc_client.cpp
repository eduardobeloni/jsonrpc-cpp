/*
 *  JsonRpc-Cpp - JSON-RPC implementation.
 *  Copyright (C) 2008-2009 Sebastien Vincent <sebastien.vincent@cppextrem.com>
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
 * \file jsonrpc_client.cpp
 * \brief JSON-RPC client.
 * \author Sebastien Vincent
 */

#include "jsonrpc_client.h"

#include <cstring>

namespace Json
{

  namespace Rpc
  {

    Client::Client(const std::string& address, uint16_t port)
    {
      m_sock = -1;
      m_address = address;
      m_port = port;
      SetEncapsulatedFormat(Json::Rpc::RAW);
    }

    Client::~Client()
    {
      if(m_sock != -1)
      {
        Close();
      }
    }

    void Client::SetEncapsulatedFormat(enum EncapsulatedFormat format)
    {
      m_format = format;
    }

    enum EncapsulatedFormat Client::GetEncapsulatedFormat() const
    {
      return m_format;
    }

    int Client::GetSocket() const
    {
      return m_sock;
    }

    std::string Client::GetAddress() const
    {
      return m_address;
    }

    uint16_t Client::GetPort() const
    {
      return m_port;
    }

    void Client::Close()
    {
      ::close(m_sock);
      m_sock = -1;
    }

  } /* namespace Rpc */

} /* namespace Json */

