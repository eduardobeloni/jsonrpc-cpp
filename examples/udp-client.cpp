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
 * \file udp-client.cpp
 * \brief Simple JSON-RPC UDP client.
 * \author Sebastien Vincent
 */

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "../src/jsonrpc.h"

/**
 * \brief Entry point of the program.
 * \param argc number of argument
 * \param argv array of arguments
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char** argv)
{
  Json::Rpc::UdpClient udpClient(std::string("127.0.0.1"), 8086);
  Json::Value query;
  Json::FastWriter writer;
  std::string queryStr;
  std::string responseStr;

  /* avoid compilation warnings */
  argc = argc;
  argv = argv;

  if(!udpClient.Connect())
  {
    std::cout << "Cannot connect to remote peer!" << std::endl;
    exit(EXIT_FAILURE);
  }

  /* build JSON-RPC query */
  query["jsonrpc"] = "2.0";
  query["id"] = 1;
  query["method"] = "system.print";

  queryStr = writer.write(query);
  std::cout << "Query is: " << queryStr << std::endl;

  if(udpClient.Send(queryStr) == -1)
  {
    std::cout << "Error while sending data!" << std::endl;
    exit(EXIT_FAILURE);
  }
  
  /* wait the response */
  if(udpClient.Recv(responseStr) != -1)
  {
    std::cout << "Received: " << responseStr << std::endl;
  }
  else
  {
    std::cout << "Error while receiving data!" << std::endl;
  }

  udpClient.Close();

  return EXIT_SUCCESS;
}

