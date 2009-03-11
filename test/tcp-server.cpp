/**
 * \file tcp-server.cpp
 * \brief Simple JSON-RPC TCP server.
 * \author Sebastien Vincent
 */

#include <cstdio>
#include <cstdlib>

#include <jsonrpc/jsonrpc.h>

#include "test.h"

/**
 * \brief Entry point of the program.
 * \param argc number of argument
 * \param array of arguments
 * \return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char** argv)
{
  Test a;
  Json::Rpc::TcpServer server(std::string("127.0.0.1"), 8086);

  /* to avoid compilation warnings */
  argc = argc;
  argv = argv;

  server.AddMethod(new Json::Rpc::RpcMethod<Test>(a, &Test::Print, std::string("system.print")));

  if(!server.Bind())
  {
    std::cout << "Bind failed" << std::endl;
    return -1;
  }

  if(!server.Listen())
  {
    std::cout << "Listen failed" << std::endl;
    return -1;
  }

  while(1)
  {
    server.WaitMessage(1000);
  }

  return 0;
}

