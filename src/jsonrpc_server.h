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
 * \file jsonrpc_server.h
 * \brief JSON-RPC server.
 * \author Sebastien Vincent
 */

#ifndef JSONRPC_SERVER_H
#define JSONRPC_SERVER_H

#include "jsonrpc_handler.h"

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <unistd.h>

#include <netinet/in.h>

#include <netdb.h>

#else
#include <winsock2.h>
#endif

namespace Json
{

  namespace Rpc
  {
    /**
     * \enum EncapsulatedFormat
     * \brief JSON-RPC message encoding format (nothing to do with UTF-8 or languages).
     */
    enum EncapsulatedFormat
    {
      RAW, /**< Raw format. */ 
      NETSTRING, /**< Encapsulate the message with NetString (see http://cr.yp.to/proto/netstrings.txt). */
#if 0
      HTTP_POST, /**< Encapsulate the message in HTTP POST. */
      HTTP_GET, /**< Encapsulate the message in HTTP POST. */
#endif
    };

    /**
     * \enum TransportProtocol
     * \brief Transport protocol.
     */
    enum TransportProtocol
    {
      UDP = IPPROTO_UDP, /**< UDP protocol. */
      TCP = IPPROTO_TCP, /**< TCP protocol. */
    };

    /**
     * \class Server
     * \brief Abstract JSON-RPC server.
     */
    class Server
    {
      public:
        /**
         * \brief Constructor.
         * \param address network address or FQDN to bind
         * \param port local port to bind
         */
        Server(const std::string& address, uint16_t port);

        /**
         * \brief Destructor.
         */
        virtual ~Server();

        /**
         * \brief Wait message.
         *
         * This function do a select() on the socket and Process() immediately 
         * the JSON-RPC message.
         * \param ms millisecond to wait (0 means infinite)
         */
        virtual void WaitMessage(uint32_t ms) = 0;

        /**
         * \brief Set the encapsulated format (default is RAW).
         * \param format encapsulated format
         */
        void SetEncapsulatedFormat(enum EncapsulatedFormat format);

        /**
         * \brief Get the encapsulated format.
         * \return encapsulated format
         */
        enum EncapsulatedFormat GetEncapsulatedFormat() const;

        /**
         * \brief Get socket descriptor.
         * \return socket descriptor.
         */
        int GetSocket() const;

        /**
         * \brief Get the address.
         * \return address or FQDN
         */
        std::string GetAddress() const;

        /**
         * \brief Get the port.
         * \return local port
         */
        uint16_t GetPort() const;

        /**
         * \brief Bind the socket.
         * \return true if success, false otherwise
         */
        bool Bind();

        /**
         * \brief Add a RPC method.
         * \param method RPC method
         */
        void AddMethod(CallbackMethod* method);

      protected:
        /**
         * \brief Socket descriptor.
         */
        int m_sock;

        /**
         * \brief Transport protocol of the socket.
         */
        enum TransportProtocol m_protocol;

        /**
         * \brief JSON-RPC handler.
         */
        Handler m_jsonHandler;

      private:
        /**
         * \brief Network address or FQDN.
         */
        std::string m_address;

        /**
         * \brief Local port.
         */
        uint16_t m_port;

        /**
         * \brief Encapsulated format.
         */
        enum EncapsulatedFormat m_format;
    };

  } /* namespace Rpc */

} /* namespace Json */

#endif /* JSONRPC_SERVER_H */

