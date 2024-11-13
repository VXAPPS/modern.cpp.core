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
#include <cstdint> // std::int32_t

/* stl header */
#include <variant>

/* local header */
#include "Point.h"
#include "Size.h"
#include "TypeCheck.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template for rect.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   * @tparam T   Type.
   */
  template <typename T>
  class Rect : private TypeCheck<isVariantMember<T, std::variant<std::int32_t, float, double>>::value> {

  public:
    /**
     * @brief Default constructor for Rect.
     */
    constexpr Rect() = default;

    /**
     * @brief Constructor for Rect.
     * @param _left   X value.
     * @param _top   Y value.
     * @param _width   Width value.
     * @param _height   Height value.
     */
    constexpr Rect( T _left,
                    T _top,
                    T _width,
                    T _height ) noexcept
      : m_x1( _left ),
        m_y1( _top ),
        m_x2( _left + _width - 1 ),
        m_y2( _top + _height - 1 ) {}

    /**
     * @brief Constructor for Rect.
     * @param _topleft   Top left point.
     * @param _bottomright   Bottom right point.
     */
    constexpr Rect( Point<T> _topleft,
                    Point<T> _bottomright ) noexcept
      : m_x1( _topleft.x() ),
        m_y1( _topleft.y() ),
        m_x2( _bottomright.x() ),
        m_y2( _bottomright.y() ) {}

    /**
     * @brief Constructor for Rect.
     * @param _point   Point value.
     * @param _size   Size value.
     */
    constexpr Rect( Point<T> _point,
                    Size<T> _size ) noexcept
      : m_x1( _point.x() ),
        m_y1( _point.y() ),
        m_x2( _point.x() + _size.width() - 1 ),
        m_y2( _point.y() + _size.height() - 1 ) {}

    /**
     * @brief Check if the rect is null.
     * @return True, if the rect is null - otherwise false.
     */
    [[nodiscard]] constexpr bool null() const noexcept { return floating_point::equal( m_x2, m_x1 - 1 ) && floating_point::equal( m_y2, m_y1 - 1 ); }

    /**
     * @brief Check if the rect is empty.
     * @return True, if the rect is empty - otherwise false.
     */
    [[nodiscard]] constexpr bool empty() const noexcept { return floating_point::greater( m_x1, m_x2 ) || floating_point::greater( m_y1, m_y2 ); }

    /**
     * @brief Check if the rect is valid.
     * @return True, if the rect is valid - otherwise false.
     */
    [[nodiscard]] constexpr bool valid() const noexcept { return floating_point::less( m_x1, m_x2, true ) && floating_point::less( m_y1, m_y2, true ); }

    /**
     * @brief Return left coordinate.
     * @return The left coordinate.
     */
    [[nodiscard]] constexpr T left() const noexcept { return m_x1; }

    /**
     * @brief Return top coordinate.
     * @return The bottom coordinate.
     */
    [[nodiscard]] constexpr T top() const noexcept { return m_y1; }

    /**
     * @brief Return right coordinate.
     * @return The right coordinate.
     */
    [[nodiscard]] constexpr T right() const noexcept { return m_x2; }

    /**
     * @brief Return bottom coordinate.
     * @return The bottom coordinate.
     */
    [[nodiscard]] constexpr T bottom() const noexcept { return m_y2; }

    /**
     * @brief Return x coordinate of point.
     * @return The x coordinate of point.
     */
    [[nodiscard]] constexpr T x() const noexcept { return m_x1; }

    /**
     * @brief Return y coordinate of point.
     * @return The y coordinate of point.
     */
    [[nodiscard]] constexpr T y() const noexcept { return m_y1; }

    /**
     * @brief Return width.
     * @return The width.
     */
    [[nodiscard]] constexpr T width() const noexcept { return m_x2 - m_x1 + 1; }

    /**
     * @brief Return height.
     * @return The height.
     */
    [[nodiscard]] constexpr T height() const noexcept { return m_y2 - m_y1 + 1; }

    /**
     * @brief Set left.
     * @param _left   The new left.
     */
    inline void setLeft( T _left ) noexcept { m_x1 = _left; }

    /**
     * @brief Set top.
     * @param _top   The new top.
     */
    inline void setTop( T _top ) noexcept { m_y1 = _top; }

    /**
     * @brief Set right.
     * @param _right   The new right.
     */
    inline void setRight( T _right ) noexcept { m_x2 = _right; }

    /**
     * @brief Set bottom.
     * @param _bottom   The new bottom.
     */
    inline void setBottom( T _bottom ) noexcept { m_y2 = _bottom; }

    /**
     * @brief Set width.
     * @param _width   The new width.
     */
    inline void setWidth( T _width ) noexcept { m_x2 = m_x1 + _width - 1; }

    /**
     * @brief Set height.
     * @param _height   The new height.
     */
    inline void setHeight( T _height ) noexcept { m_y2 = m_y2 + _height - 1; }

    /**
     * @brief Unite current rect with rect.
     * @param _rectangle   The rectangle to unite with current rect.
     * @return The united new rect.
     */
    [[nodiscard]] constexpr Rect<T> operator|( Rect<T> _rectangle ) const noexcept;

    /**
     * @brief Intersect current rect with rect.
     * @param _rectangle   The rectangle to intersect with current rect.
     * @return The interesected new rest.
     */
    [[nodiscard]] constexpr Rect<T> operator&( Rect<T> _rectangle ) const noexcept;

    /**
     * @brief Unite current rect with rect.
     * @param _rectangle   The rectangle to unite with current rect.
     * @return The united new rect.
     */
    [[nodiscard]] constexpr Rect<T> &operator|=( Rect<T> _rectangle ) noexcept;

    /**
     * @brief Intersect current rect with rect.
     * @param _rectangle   The rectangle to intersect with current rect.
     * @return The interesected new rest.
     */
    [[nodiscard]] constexpr Rect<T> &operator&=( Rect<T> _rectangle ) noexcept;

    /**
     * @brief Current rect contains rect.
     * @param _rectangle   Rectangle which is contained by current rect.
     * @return True, if current rect contains rect - otherwise false.
     */
    [[nodiscard]] bool contains( Rect<T> _rectangle ) const noexcept;

    /**
     * @brief Intersect current rect with rect.
     * @param _rectangle   The rectangle to intersect with current rect.
     * @return The interesected new rest.
     */
    [[nodiscard]] constexpr Rect<T> intersected( Rect<T> _rectangle ) const noexcept { return *this & _rectangle; }

    /**
     * @brief Current rect intersects rect.
     * @param _rectangle   Rectangle which is intersected by current rect.
     * @return True, if current rect intersects rect - otherwise false.
     */
    [[nodiscard]] bool intersects( Rect<T> _rectangle ) const noexcept;

    /**
     * @brief Unite current rect with rect.
     * @param _rectangle   The rectangle to unite with current rect.
     * @return The united new rect.
     */
    [[nodiscard]] constexpr Rect<T> united( Rect<T> _rectangle ) const noexcept { return *this | _rectangle; }

    /**
     * @brief Equal operator.
     * @param _rect   Rect to compare with.
     * @return True, if the compared rect is equal current rect - otherwise false.
     */
    [[nodiscard]] constexpr bool operator==( Rect<T> _rect ) const noexcept { return floating_point::equal( m_x1, _rect.m_x1 ) && floating_point::equal( m_y1, _rect.m_y1 ) && floating_point::equal( m_x2, _rect.m_x2 ) && floating_point::equal( m_y2, _rect.m_y2 ); }

  private:
    /**
     * @brief Member for x coordinate of point1.
     */
    T m_x1 = 0;

    /**
     * @brief Member for y coordinate of point1.
     */
    T m_y1 = 0;

    /**
     * @brief Member for x coordinate of point2.
     */
    T m_x2 = 1;

    /**
     * @brief Member for y coordinate of point2.
     */
    T m_y2 = 1;
  };

  /**
   * @brief Template argument deduction.
   * @tparam T   Type.
   */
  template <typename T>
  Rect( T ) -> Rect<T>;

  /**
   * @brief Current rect contains rect.
   * @param _rectangle   Rectangle which is contained by current rect.
   * @return True, if current rect contains rect - otherwise false.
   */
  extern template bool Rect<int>::contains( Rect<int> _rectangle ) const noexcept;

  /**
   * @brief Current rect contains rect.
   * @param _rectangle   Rectangle which is contained by current rect.
   * @return True, if current rect contains rect - otherwise false.
   */
  extern template bool Rect<float>::contains( Rect<float> _rectangle ) const noexcept;

  /**
   * @brief Current rect contains rect.
   * @param _rectangle   Rectangle which is contained by current rect.
   * @return True, if current rect contains rect - otherwise false.
   */
  extern template bool Rect<double>::contains( Rect<double> _rectangle ) const noexcept;

  /**
   * @brief Current rect intersects rect.
   * @param _rectangle   Rectangle which is intersected by current rect.
   * @return True, if current rect intersects rect - otherwise false.
   */
  extern template bool Rect<int>::intersects( Rect<int> _rectangle ) const noexcept;

  /**
   * @brief Current rect intersects rect.
   * @param _rectangle   Rectangle which is intersected by current rect.
   * @return True, if current rect intersects rect - otherwise false.
   */
  extern template bool Rect<float>::intersects( Rect<float> _rectangle ) const noexcept;

  /**
   * @brief Current rect intersects rect.
   * @param _rectangle   Rectangle which is intersected by current rect.
   * @return True, if current rect intersects rect - otherwise false.
   */
  extern template bool Rect<double>::intersects( Rect<double> _rectangle ) const noexcept;
}
