/**
 * \file test.h
 * \brief Test example.
 * \author Sebastien Vincent
 */

#ifndef TEST_H
#define TEST_H 

#include <json/json.h>

/**
 * \class Test
 * \brief Example.
 */
class Test
{
  public:
    /**
     * \brief Reply with success.
     * \param root JSON-RPC request
     * \param response JSON-RPC response
     * \return true if correctly processed, false otherwise
     */
    bool Print(const Json::Value& root, Json::Value& response);

    /**
     * \brief Get the description in JSON format.
     * \return JSON description
     */
    Json::Value GetDescription();
};


#endif /* TEST_H */

