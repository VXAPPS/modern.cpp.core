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
#include <cmath> // std::abs
#include <cstdint> // std::int32_t

/* stl header */
#include <variant>

/* local header */
#include "FloatingPoint.h"
#include "TypeCheck.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template for point.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   * @tparam T   Type.
   */
  template <typename T>
  class Point : private TypeCheck<isVariantMember<T, std::variant<std::int32_t, float, double>>::value> {

  public:
    /**
     * @brief Default constructor for Point.
     */
    constexpr Point<T>() = default;

    /**
     * @brief Constructor for Point.
     * @param _x   X value.
     * @param _y   Y value.
     */
    constexpr Point<T>( T _x,
                        T _y ) noexcept
      : m_x( _x ),
        m_y( _y ) {}

    /**
     * @brief Check if the point is null.
     * @return True, if the point is null - otherwise false.
     */
    [[nodiscard]] constexpr bool null() const noexcept { return floating_point::equal( m_x, static_cast<T>( 0 ) ) && floating_point::equal( m_y, static_cast<T>( 0 ) ); }

    /**
     * @brief Return x coordinate of point.
     * @return The x coordinate of point.
     */
    [[nodiscard]] constexpr T x() const noexcept { return m_x; }

    /**
     * @brief Return y coordinate of point.
     * @return The y coordinate of point.
     */
    [[nodiscard]] constexpr T y() const noexcept { return m_y; }

    /**
     * @brief Set x coordinate of point.
     * @param _x   The x coordinate of point.
     */
    inline void setX( T _x ) noexcept { m_x = _x; }

    /**
     * @brief Set y coordinate of point.
     * @param _y   The y coordinate of point.
     */
    inline void setY( T _y ) noexcept { m_y = _y; }

    /**
     * @brief Calculate manhattan length.
     * @return Manhattan length.
     */
    [[nodiscard]] constexpr T manhattanLength() const noexcept { return std::abs( m_x ) + std::abs( m_y ); }

    /**
     * @brief Adding point.
     * @param _point   Point to add.
     * @return The calculated new point.
     */
    constexpr Point<T> &operator+=( Point<T> _point ) noexcept {

      m_x += _point.m_x;
      m_y += _point.m_y;
      return *this;
    }

    /**
     * @brief Substract point.
     * @param _point   Point to subtract.
     * @return The calculated new point.
     */
    constexpr Point<T> &operator-=( Point<T> _point ) noexcept {

      m_x -= _point.m_x;
      m_y -= _point.m_y;
      return *this;
    }

    /**
     * @brief Equal operator.
     * @param _point   Point to compare with.
     * @return True, if the compared point is equal current point - otherwise false.
     */
    [[nodiscard]] constexpr bool operator==( Point<T> _point ) const noexcept { return floating_point::equal( m_x, _point.m_x ) && floating_point::equal( m_y, _point.m_y ); }

  private:
    /**
     * @brief Member for x coordinate.
     */
    T m_x = 0;

    /**
     * @brief Member for y coordinate.
     */
    T m_y = 0;
  };

  /**
   * @brief Template argument deduction.
   * @tparam T   Type.
   */
  template <typename T>
  Point( T ) -> Point<T>;
}
