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
 * \file networking.cpp
 * \brief Networking utils.
 * \author Sebastien Vincent
 */

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#endif

namespace networking
{
#ifdef _WIN32
  /**
   * \var wsaData
   * \brief MS Windows object to start
   * networking stuff.
   */
  static WSAData wsaData;
#endif

  bool init()
  {
    bool ret = false;

#ifdef _WIN32
    ret = (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0);
#else
    ret = true;
#endif

    return ret;
  }

  void cleanup()
  {
#ifdef _WIN32
    WSACleanup();
#endif
  }
} /* namespace networking */

