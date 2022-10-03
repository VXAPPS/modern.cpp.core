/*
 * Copyright (c) 2011 Florian Becker <fb@vxapps.com> (VX APPS).
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

/* c header */
#include <cmath>

/* stl header */
#include <variant>

/* local header */
#include "FloatingPoint.h"
#include "TypeCheck.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  template <typename T>
  class Point : TypeCheck<isVariantMember<T, std::variant<int, float, double>>::value> {

  public:
    constexpr Point<T>() = default;

    constexpr Point<T>( T _x,
                        T _y ) noexcept
      : m_x( _x ),
        m_y( _y ) {}

    [[nodiscard]] inline constexpr bool null() const noexcept { return floating_point::equal( m_x, static_cast<T>( 0 ) ) && floating_point::equal( m_y, static_cast<T>( 0 ) ); }

    [[nodiscard]] inline constexpr T x() const noexcept { return m_x; }

    [[nodiscard]] inline constexpr T y() const noexcept { return m_y; }

    inline void setX( T _x ) noexcept { m_x = _x; }

    inline void setY( T _y ) noexcept { m_y = _y; }

    [[nodiscard]] inline constexpr T manhattanLength() const noexcept { return std::abs( m_x ) + std::abs( m_y ); }

    inline constexpr Point<T> &operator+=( Point<T> _point ) noexcept {

      m_x += _point.m_x;
      m_y += _point.m_y;
      return *this;
    }

    inline constexpr Point<T> &operator-=( Point<T> _point ) noexcept {

      m_x -= _point.m_x;
      m_y -= _point.m_y;
      return *this;
    }

    [[nodiscard]] inline constexpr bool operator==( Point<T> _point ) const noexcept { return floating_point::equal( m_x, _point.m_x ) && floating_point::equal( m_y, _point.m_y ); }

    [[nodiscard]] inline constexpr bool operator!=( Point<T> _point ) const noexcept { return !floating_point::equal( m_x, _point.m_x ) || !floating_point::equal( m_y, _point.m_y ); }

  private:
    T m_x = 0;
    T m_y = 0;
  };

  /* template argument deduction */
  template <typename T>
  Point( T ) -> Point<T>;
}
