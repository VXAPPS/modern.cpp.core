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
#include <cmath>   // std::sqrt
#include <cstdint> // std::int32_t

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
  class Line : private TypeCheck<isVariantMember<T, std::variant<std::int32_t, float, double>>::value> {

  public:
    /**
     * @brief Default constructor for Line.
     */
    constexpr Line() = default;

    /**
     * @brief Constructor for Line
     * @param _point1   First point.
     * @param _point2   Second point.
     */
    constexpr Line( Point<T> _point1,
                    Point<T> _point2 ) noexcept
      : m_point1( _point1 ),
        m_point2( _point2 ) {}

    /**
     * @brief Constructor for Line.
     * @param _x1   X of first point.
     * @param _y1   Y of first point.
     * @param _x2   X of second point.
     * @param _y2   Y of second point.
     */
    constexpr Line( T _x1,
                    T _y1,
                    T _x2,
                    T _y2 ) noexcept
      : m_point1( Point<T>( _x1, _y1 ) ),
        m_point2( Point<T>( _x2, _y2 ) ) {}

    /**
     * @brief Is this line null?
     * @return True, this line has identical points - otherwise false.
     */
    [[nodiscard]] constexpr bool null() const noexcept { return m_point1 == m_point2; }

    /**
     * @brief Return point1.
     * @return Point1.
     */
    [[nodiscard]] constexpr Point<T> point1() const noexcept { return m_point1; }

    /**
     * @brief Return point2.
     * @return Point2.
     */
    [[nodiscard]] constexpr Point<T> point2() const noexcept { return m_point2; }

    /**
     * @brief Return x coordinate of point1.
     * @return The x coordinate of point1.
     */
    [[nodiscard]] constexpr T x1() const noexcept { return m_point1.x(); }

    /**
     * @brief Return y coordinate of point1.
     * @return The y coordinate of point1.
     */
    [[nodiscard]] constexpr T y1() const noexcept { return m_point1.y(); }

    /**
     * @brief Return x coordinate of point2.
     * @return The x coordinate of point2.
     */
    [[nodiscard]] constexpr T x2() const noexcept { return m_point2.x(); }

    /**
     * @brief Return y coordinate of point2.
     * @return The y coordinate of point2.
     */
    [[nodiscard]] constexpr T y2() const noexcept { return m_point2.y(); }

    /**
     * @brief Distance of x coordinates.
     * @return Return the distance of the x coordinates.
     */
    [[nodiscard]] constexpr T dx() const noexcept { return m_point2.x() - m_point1.x(); }

    /**
     * @brief Distance of y coordinates.
     * @return Return the distance of the y coordinates.
     */
    [[nodiscard]] constexpr T dy() const noexcept { return m_point2.y() - m_point1.y(); }

    /**
     * @brief Translate line by point.
     * @param _point   Point to translate.
     */
    inline void translate( Point<T> _point ) noexcept {

      m_point1 += _point;
      m_point2 += _point;
    }

    /**
     * @brief Translate line by coordinates.
     * @param _dx   X coordinate to translate.
     * @param _dy   Y coordinate to translate.
     */
    inline void translate( T _dx,
                           T _dy ) noexcept { translate( Point<T>( _dx, _dy ) ); }

    /**
     * @brief Width of this line.
     * @return The width of this line.
     */
    [[nodiscard]] constexpr T width() const noexcept { return static_cast<T>( std::sqrt( std::sqrt( m_point2.x() - m_point1.x() ) + std::sqrt( m_point2.y() - m_point1.y() ) ) ); }

  private:
    /**
     * @brief Member for point1.
     */
    Point<T> m_point1 {};

    /**
     * @brief Member for point2.
     */
    Point<T> m_point2 {};
  };

  /**
   * @brief Template argument deduction.
   * @tparam T   Type.
   */
  template <typename T>
  Line( T ) -> Line<T>;
}
