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
      CPPUNIT_TEST(testMethod);
      CPPUNIT_TEST(testJsonRpcVersion);
      CPPUNIT_TEST(testJsonRpcParsing);
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
       * \brief Test if we can add/remove method.
       */
      void testMethod()
      {
        const std::string str = "{\"jsonrpc\":\"2.0\", \"method\":\"system.print\"}";
        const std::string str2 = "{\"jsonrpc\":\"2.0\", \"method\":\"method_does_not_exist\"}";
        TestRpc obj;
        Json::Value response;

        m_handler->AddMethod(new Json::Rpc::RpcMethod<TestRpc>(obj, &TestRpc::Print, std::string("system.print")));

        CPPUNIT_ASSERT(m_handler->Process(str, response) == true);
        CPPUNIT_ASSERT(m_handler->Process(str2, response) == false);

        m_handler->DeleteMethod(std::string("system.print"));
        CPPUNIT_ASSERT(m_handler->Process(str, response) == false);
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

      /**
       * \brief Test if parsing JSON-RPC query works as expected.
       */
      void testJsonRpcParsing()
      {
        /* missing a comma */
        const std::string str = "{\"jsonrpc\":\"2.0\" \"method\":\"system.describe\"}";
        /* missing a "}" */
        const std::string str2 = "{\"jsonrpc\":\"2.0\", \"method\":\"system.describe\"";
        /* missing method parameter */
        const std::string str3 = "{\"jsonrpc\":\"2.0\", \"test\":\"system.describe\"}";
        /* "params" argument missing */
        const std::string str4 = "{\"jsonrpc\":\"2.0\", \"method\":\"system.describe\", \"params\":}";
        /* anything but not in JSON format */
        const std::string str5 = "jsonrpc blabla\n\n";
        /* valid query with array as "params"'s argument */
        const std::string str6 = "{\"jsonrpc\":\"2.0\", \"method\":\"system.describe\", \"params\":[10, 11]}";
        /* valid query with object as "params"'s argument */
        const std::string str7 = "{\"jsonrpc\":\"2.0\", \"method\":\"system.describe\", \"params\":{\"id\":1, \"value\":504}}";
        Json::Value response;

        CPPUNIT_ASSERT(m_handler->Process(str, response) == false);
        CPPUNIT_ASSERT(m_handler->Process(str2, response) == false);
        CPPUNIT_ASSERT(m_handler->Process(str3, response) == false);
        CPPUNIT_ASSERT(m_handler->Process(str4, response) == false);
        CPPUNIT_ASSERT(m_handler->Process(str5, response) == false);
        CPPUNIT_ASSERT(m_handler->Process(str6, response) == true);
        CPPUNIT_ASSERT(m_handler->Process(str7, response) == true);
      }

      private:
      /**
       * \brief Handler for JSON-RPC query.
       */
      Handler* m_handler;
    };

  } /* namespace Rpc */

} /* namespace Json */

/* add the test suite in the global registry */
CPPUNIT_TEST_SUITE_REGISTRATION(Json::Rpc::TestCore);

