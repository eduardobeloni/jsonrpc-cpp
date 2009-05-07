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
 * \file test-core.cpp
 * \brief JsonRpc-Cpp core unit tests.
 * \author Sebastien Vincent
 */

#include <cppunit/extensions/HelperMacros.h>

#include "../src/jsonrpc.h"

namespace Json
{
  namespace Rpc
  {
    /**
     * \class TestRpc
     * \brief RPC test method.
     */
    class TestRpc
    {
      public:
        /**
         * \brief Reply with success.
         * \param root JSON-RPC request
         * \param response JSON-RPC response
         * \return true if correctly processed, false otherwise
         */
        bool Print(const Json::Value& root, Json::Value& response)
        {
          response["jsonrpc"] = "2.0";
          response["id"] = root["id"];
          response["result"] = "success";
          return true;
        }
    };

    /**
     * \class TestCore
     * \brief Unit tests for core objects.
     */
    class TestCore : public CppUnit::TestFixture
    {
      CPPUNIT_TEST_SUITE(Json::Rpc::TestCore);
      CPPUNIT_TEST(testAddMethod);
      CPPUNIT_TEST(testJsonRpcVersion);
      CPPUNIT_TEST_SUITE_END();

      public:
      /**
       * \brief Initialize data before launching test.
       */
      void setUp()
      {
        m_handler = new Handler();
      }

      /**
       * \brief Cleanup data after test finished.
       */
      void tearDown()
      {
        delete m_handler;
      }

      /**
       * \brief Test if we can add method and successfully 
       * call it.
       */
      void testAddMethod()
      {
        const std::string str = "{\"jsonrpc\":\"2.0\", \"method\":\"system.print\"}";
        const std::string str2 = "{\"jsonrpc\":\"2.0\", \"method\":\"method_does_not_exist\"}";
        TestRpc obj;
        Json::Value response;

        m_handler->AddMethod(new Json::Rpc::RpcMethod<TestRpc>(obj, &TestRpc::Print, std::string("system.print")));

        CPPUNIT_ASSERT(m_handler->Process(str, response) == true);
        CPPUNIT_ASSERT(m_handler->Process(str2, response) == false);
      }

      /**
       * \brief Test if handler reject query with wrong "jsonrpc" attribute.
       */
      void testJsonRpcVersion()
      {
        const std::string str = "{\"jsonrpc\":\"2.0\", \"method\":\"system.describe\"}";
        const std::string str2 = "{\"jsonrpc\":\"1.0\", \"method\":\"system.describe\"}";
        Json::Value response;

        CPPUNIT_ASSERT(m_handler->Process(str, response) == true);
        CPPUNIT_ASSERT(m_handler->Process(str2, response) == false);
      }

      private:
      /**
       * \brief Handler for JSON-RPC query.
       */
      Handler* m_handler;
    };

  } /* namespace Rpc */

} /* namespace Json */

CPPUNIT_TEST_SUITE_REGISTRATION(Json::Rpc::TestCore);

