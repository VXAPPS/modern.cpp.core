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
#include "Point.h"
#include "TypeCheck.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template for line.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   * @tparam T   Type.
   */
  template <typename T>
  class Line : TypeCheck<isVariantMember<T, std::variant<int, float, double>>::value> {

  public:
    constexpr Line<T>() = default;

    constexpr Line<T>( Point<T> _point1,
                       Point<T> _point2 ) noexcept
      : m_point1( _point1 ),
        m_point2( _point2 ) {}

    constexpr Line<T>( T _x1,
                       T _y1,
                       T _x2,
                       T _y2 ) noexcept
      : m_point1( Point<T>( _x1, _y1 ) ),
        m_point2( Point<T>( _x2, _y2 ) ) {}

    /**
     * @brief Is this line empty?
     * @return True, this line has identical points - otherwise false.
     */
    [[nodiscard]] inline constexpr bool null() const noexcept { return m_point1 == m_point2; }

    [[nodiscard]] inline constexpr Point<T> point1() const noexcept { return m_point1; }

    [[nodiscard]] inline constexpr Point<T> point2() const noexcept { return m_point2; }

    [[nodiscard]] inline constexpr T x1() const noexcept { return m_point1.x(); }

    [[nodiscard]] inline constexpr T y1() const noexcept { return m_point1.y(); }

    [[nodiscard]] inline constexpr T x2() const noexcept { return m_point2.x(); }

    [[nodiscard]] inline constexpr T y2() const noexcept { return m_point2.y(); }

    [[nodiscard]] inline constexpr T dx() const noexcept { return m_point2.x() - m_point1.x(); }

    [[nodiscard]] inline constexpr T dy() const noexcept { return m_point2.y() - m_point1.y(); }

    inline void translate( Point<T> _point ) noexcept {

      m_point1 += _point;
      m_point2 += _point;
    }

    inline void translate( T _dx,
                           T _dy ) noexcept { translate( Point<T>( _dx, _dy ) ); }

    [[nodiscard]] inline constexpr T width() const noexcept { return static_cast<T>( std::sqrt( std::sqrt( m_point2.x() - m_point1.x() ) + std::sqrt( m_point2.y() - m_point1.y() ) ) ); }

  private:
    Point<T> m_point1 {};
    Point<T> m_point2 {};
  };

  /* template argument deduction */
  template <typename T>
  Line( T ) -> Line<T>;
}
