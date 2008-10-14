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
 * \file jsonrpc_handler.cpp
 * \brief JSON-RPC processor engine.
 * \author Sebastien Vincent
 */

#include "jsonrpc_handler.h"

namespace Json
{

  namespace Rpc
  {

    CallbackMethod::~CallbackMethod()
    {
    }

    Handler::Handler()
    {
      /* add a RPC method that list the actual RPC methods contained in the Handler */
      Json::Value root;

      root["description"] = "List the RPC methods available";
      root["parameters"] = Json::Value::null;
      root["returns"] = "Object that contains description of all methods registered";

      AddMethod(new RpcMethod<Handler>(*this, &Handler::SystemDescribe, std::string("system.describe"), root));
    }

    Handler::~Handler()
    {
      /* delete all objects from the list */
      for(std::list<CallbackMethod*>::const_iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        delete (*it);
      }
      m_methods.clear();
    }

    void Handler::AddMethod(CallbackMethod* method)
    {
      m_methods.push_back(method);
    }

    void Handler::DeleteMethod(const std::string& name)
    {
      /* do not delete system defined method */
      if(name == "system.describe")
      {
        return;
      }

      for(std::list<CallbackMethod*>::iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        if((*it)->GetName() == name)
        {
          m_methods.erase(it);
          delete (*it);
          break;
        }
      }
    }

    bool Handler::SystemDescribe(const Json::Value& msg, Json::Value& response)
    {
      Json::Value methods;
      response["jsonrpc"] = "2.0";
      response["id"] = msg["id"];

      for(std::list<CallbackMethod*>::iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        methods[(*it)->GetName()] = (*it)->GetDescription();
      }
      
      response["methods"] = methods;
      return false;
    }

    std::string Handler::GetString(Json::Value value)
    {
      return m_writer.write(value);
    }

    bool Handler::Check(const std::string& msg, Json::Value& root)
    {
      bool parsing = m_reader.parse(msg, root);

      /* if one thing goes wrong, we forge an error attribute that
       * will be added to a JSON-RPC error message 
       */
      if(!parsing)
      {
        root = Json::Value();
        root["code"] = PARSING_ERROR;
        root["message"] = "Parse error";
        
        return false;
      }

      /* check the JSON-RPC version => 2.0 */
      if(!root.isObject() || !root.isMember("jsonrpc") || root["jsonrpc"] != "2.0") 
      {
        root = Json::Value();
        root["code"] = INVALID_REQUEST;
        root["message"] = "Invalid JSON-RPC";
        
        return false;
      }

      return true;
    }

    bool Handler::Process(const std::string& msg, Json::Value& response)
    {
      Json::Value root;
      std::string method;

      if(!Check(msg, root))
      {
        response["jsonrpc"] = "2.0";
        response["error"] = root;
        response["id"] = Json::Value::null;
        return false;
      }

      /* extract "method" attribute */
      if(!root.isMember("method") || !root["method"].isString())
      {
        response["id"] = Json::Value::null;
        response["jsonrpc"] = "2.0";

        Json::Value error;
        error["code"] = INVALID_REQUEST;
        error["message"] = "Invalid JSON-RPC";
        response["error"] = error;
        return false;
      }

      method = root["method"].asString();
      if(method != "")
      {
        CallbackMethod* rpc = Lookup(method);
        if(rpc)
        {
          return rpc->Call(root, response);
        }
      }

      /* forge an error response */
      response["id"] = root.isMember("id") ? root["id"] : Json::Value::null;
      response["jsonrpc"] = "2.0";

      Json::Value error;
      error["code"] = METHOD_NOT_FOUND;
      error["message"] = "Procedure not found";
      response["error"] = error;

      return false;
    }

    bool Handler::Process(const char* msg, Json::Value& response)
    {
      std::string str(msg);

      return Process(str, response);
    }

    CallbackMethod* Handler::Lookup(const std::string& name) const
    {
      for(std::list<CallbackMethod*>::const_iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        if((*it)->GetName() == name)
        {
          return (*it);
        }
      }

      return 0;
    }

  } /* namespace Rpc */

} /* namespace Json */

#if 0

/* test */

class Plop
{
  public:
    bool Print(const Json::Value& root, Json::Value& response)
    {
      std::cout << "Plop" << std::endl;
      response["jsonrpc"] = 2.0;
      response["id"] = root["id"];
      response["result"] = "success";
      return true;
    }
};

int main(int argc, char** argv)
{
  const std::string str = "{\"jsonrpc\": \"2.0\", \"method\": \"system.print\", \"params\": [42, 23], \"id\": 1, \"dd\": null}";
  Json::Rpc::Handler jsonHandler;
  Plop a;
  Json::Value response;
  const std::string strMethod = "system.print";
  Json::Rpc::RpcMethod<Plop>* method = new Json::Rpc::RpcMethod<Plop>(a, &Plop::Print, strMethod);

  jsonHandler.AddMethod(method);
  if(jsonHandler.Process(str, response))
  {
    std::cout << response << std::endl;
  }

  jsonHandler.DeleteMethod("system.print");

  jsonHandler.Process(str, response);
  std::cout << response << std::endl;
  return 0;
}

#endif

