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
 * \file netstring.cpp
 * \brief NetString implementation (http://cr.yp.to/proto/netstrings.txt).
 * \author Sebastien Vincent
 */

#include "netstring.h"

#include <iostream>
#include <stdexcept>

#include <cstdio>

namespace netstring
{
  std::string encode(const std::string& str)
  {
    unsigned long len = str.length();
    char strLen[32];
    std::string ret;
    
    /* format of a netstring is [len]:[string], */
    sprintf(strLen, "%lu:", len);
    ret.append(strLen);
    ret.append(str);
    ret.append(",");

    return ret;
  }

  std::string decode(const std::string& str)
  {
    unsigned long len = 0;
    size_t index = 0; /* position of ":" */
    size_t index2 = 0; /* position of "," */
    size_t i = 0;
    const char* data = str.data();
    std::string ret;

    index = str.find_first_of(":");
    if(index == std::string::npos)
    {
      /* error */
      throw std::runtime_error("netstring error : missing ':' character");
    }
    
    index2 = str.find_last_of(",");
    if(index2 == std::string::npos)
    {
      /* error */
      throw std::runtime_error("netstring error : missing ',' character");
    }

    for(i = 0 ; i < index ; i++)
    {
      if(isdigit(data[i]))
      {
        len = len * 10 + (data[i] - (char)0x30);
      }
      else
      {
        /* error */
        throw std::runtime_error("netstring error : parsing error");
      }
    }

    if(len != str.length() - index - 2)
    {
      /* error */
      throw std::runtime_error("netstring error : size mismatch");
    }

    ret.assign(str, index + 1, len);
    return ret;
  }

} /* namespace netstring */

#if 0 

/* test */

int main(int argc, char** argv)
{
  std::string a = netstring::encode("hello world!");
  std::string b = netstring::decode(a);
  
  std::cout << a << std::endl;
  std::cout << b << std::endl;

  try
  {
    
    /* length field too long */
    /* a = netstring::decode("13:hello world!,"); */
    /* length field too small */
    /* a = netstring::decode("11:hello world!,"); */
    /* string too long */
    /* a = netstring::decode("12:hello world!!,"); */
    /* missing "," */
    /* a = netstring::decode("12:hello world!"); */
    /* missing ":" */
    a = netstring::decode("12hello world!,");

  }
  catch(std::runtime_error e)
  {
    std::cout << "Exception raised : " << e.what() << std::endl;
  }

  return 0;
}

#endif

