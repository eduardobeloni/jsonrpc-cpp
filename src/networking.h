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
 * \file networking.h
 * \brief Networking utils.
 * \author Sebastien Vincent
 */

/**
 * \namespace networking
 * \brief Networking related functions.
 */
namespace networking
{
  /**
   * \brief Initialize networking.
   * \return true if network is correctly initialized
   * \note On MS Windows, this step is mandatory to use
   * socket API (socket(), bind(), recvfrom(), ...).
   */
  bool init();

  /**
   * \brief Cleanup networking.
   * \note On MS Windows, after calling this function,
   * it will be impossible to use socket API.
   */
  void cleanup();

} /* namespace networking */

