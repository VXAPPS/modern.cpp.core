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

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template instance class.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  template<class T>
  class Singleton {

  public:
    /**
     * @brief @~english C++11 Singleton thread-safe. @~german C++11 Singleton thread-safe.
     * @return @~english Singleton of T. @~german Einzige Instanz von T.
     */
    static T &instance() {

#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
      static T instance;
      return instance;
#if defined(__clang__)
  #pragma clang diagnostic pop
#endif
    }

    /**
     * @brief @~english Delete move constructor. @~german Entfernt den verschobenen Konstruktor.
     */
    Singleton( Singleton && ) = delete;

    /**
     * @brief @~english Delete copy assign. @~german Entfernt die kopierte Zuweisung.
     * @return @~english Nothing. @~german Keine Rückgabe.
     */
    Singleton &operator=( Singleton const & ) = delete;

    /**
     * @brief @~english Delete move assign. @~german Entfernt die verschobene Zuweisung.
     * @return @~english Nothing. @~german Keine Rückgabe.
     */
    Singleton &operator=( Singleton && ) = delete;

  protected:
    /**
     * @brief @~english Default constructor for Singleton. @~german Standardkonstruktur für Singleton.
     */
    Singleton() = default;

    /**
     * @brief @~english Default destructor for Singleton. @~german Standarddestruktor für Singleton.
     */
    ~Singleton() = default;
  };
}
