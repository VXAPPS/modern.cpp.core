/*
 * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

namespace vx {

  /**
   * @brief Template instance class.
   * @author Florian Becker <fb\@vxapps.com> (VX Apps)
   */
  template<class T>
  class SingletonBase {

  public:
    /**
     * @~english
     * @brief C++11 Singleton thread-safe.
     * @return Singleton of T.
     *
     * @~german
     * @brief C++11 Singleton thread-safe.
     * @return Einzige Instanz von T.
     */
    static T &instance() {

      static T instance;
      return instance;
    }

    /**
     * @~english
     * @brief Delete move constructor.
     *
     * @~german
     * @brief Entfernt den verschobenen Konstruktor.
     */
    SingletonBase( SingletonBase && ) = delete;

    /**
     * @~english
     * @brief Delete copy assign.
     * @return Nothing.
     *
     * @~german
     * @brief Entfernt die kopierte Zuweisung.
     * @return Keine Rückgabe.
     */
    SingletonBase &operator=( SingletonBase const & ) = delete;

    /**
     * @~english
     * @brief Delete move assign.
     * @return Nothing.
     *
     * @~german
     * @brief Entfernt die verschobene Zuweisung.
     * @return Keine Rückgabe.
     */
    SingletonBase &operator=( SingletonBase && ) = delete;

  protected:
    /**
     * @~english
     * @brief Default constructor for InstanceBase.
     *
     * @~german
     * @brief Standardkonstruktur für InstanceBase.
     */
    SingletonBase() = default;

    /**
     * @~english
     * @brief Default destructor for InstanceBase.
     *
     * @~german
     * @brief Standarddestruktor für InstanceBase.
     */
    virtual ~SingletonBase() = default;
  };
}
