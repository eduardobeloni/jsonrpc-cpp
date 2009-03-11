/**
 * \file test.cpp
 * \brief Test example.
 * \author Sebastien Vincent
 */

#include "test.h"

bool Test::Print(const Json::Value& root, Json::Value& response)
{
  std::cout << "Plop" << std::endl;
  response["jsonrpc"] = "2.0";
  response["id"] = root["id"];
  response["result"] = "success";
  return true;
}

Json::Value Test::GetDescription()
{
  Json::FastWriter writer;
  Json::Value root;
  Json::Value parameters;
  Json::Value param1;

  root["description"] = "Print Plop";

  /* type of parameter named arg1 */
  param1["type"] = "integer";
  param1["description"] = "argument 1";

  /* push it into the parameters list */
  parameters["arg1"] = param1;
  root["parameters"] = parameters;

  /* no value returned */
  root["returns"] = Json::Value::null;

  return root;
}

