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
 * \file netstring.h
 * \brief NetString implementation (http://cr.yp.to/proto/netstrings.txt).
 * \author Sebastien Vincent
 * \todo Add a subclass of exception to manage netstring exceptions.
 */

#ifndef NETSTRING_H
#define NETSTRING_H 

#include <string>

/**
 * \namespace netstring
 * \brief Netstring related functions.
 * \see http://cr.yp.to/proto/netstrings.txt
 */
namespace netstring
{
  /**
   * \brief Encode a string into netstring.
   * \param str string to encode
   * \return encoded netstring
   */
  std::string encode(const std::string& str);

  /**
   * \brief Decode a netstring into string.
   * \param netstr netstring
   * \return decoded string
   */
  std::string decode(const std::string& netstr);

} /* namespace netstring */

#endif /* NETSTRING_H */

