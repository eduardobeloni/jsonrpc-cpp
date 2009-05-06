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
 * \file jsonrpc_udpclient.h
 * \brief JSON-RPC UDP client.
 * \author Sebastien Vincent
 */

#ifndef JSONRPC_UDPCLIENT_H 
#define JSONRPC_UDPCLIENT_H 

#include <iostream>

#include "jsonrpc_client.h"

namespace Json
{

  namespace Rpc
  {
    /**
     * \class UdpClient
     * \brief JSON-RPC UDP client.
     */
    class UdpClient : public Client
    {
      public:
        /**
         * \brief Constructor.
         * \param address network address or FQDN to bind
         * \param port local port to bind
         */
        UdpClient(const std::string& address, uint16_t port);

        /**
         * \brief Destructor.
         */
        virtual ~UdpClient();

        /**
         * \brief Connect to the remote machine
         * \return true if success, false otherwise
         * \note on connectionless protocol like UDP, this function
         * always returns true even if remote peer is not reachable.
         */
        virtual bool Connect(); 

        /**
         * \brief Receive data from the network.
         * \param data if data is received it will put in this reference
         * \return number of bytes received or -1 if error
         * \note This method will blocked until data comes.
         */
        virtual ssize_t Recv(std::string& data);
        
        /**
         * \brief Send data.
         * \param data data to send
         * \return number of bytes sent or -1 if error
         */
        ssize_t Send(const std::string& data);

      private:
        /**
         * \brief Remote socket address.
         */
        struct sockaddr_storage m_sockaddr;
        
        /**
         * \brief Remote socket address length.
         */
        socklen_t m_sockaddrlen;
    };

  } /* namespace Rpc */

} /* namespace Json */

#endif /* JSONRPC_UDPCLIENT_H */

