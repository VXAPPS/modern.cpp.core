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
  class Rect : private TypeCheck<isVariantMember<T, std::variant<int, float, double>>::value> {

  public:
    /**
     * @brief Default constructor for Rect.
     */
    constexpr Rect<T>() = default;

    /**
     * @brief Constructor for Rect.
     * @param _left   X value.
     * @param _top   Y value.
     * @param _width   Width value.
     * @param _height   Height value.
     */
    constexpr Rect<T>( T _left,
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
    constexpr Rect<T>( Point<T> _topleft,
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
    constexpr Rect<T>( Point<T> _point,
                       Size<T> _size ) noexcept
      : m_x1( _point.x() ),
        m_y1( _point.y() ),
        m_x2( _point.x() + _size.width() - 1 ),
        m_y2( _point.y() + _size.height() - 1 ) {}

    [[nodiscard]] constexpr bool null() const noexcept { return floating_point::equal( m_x2, m_x1 - 1 ) && floating_point::equal( m_y2, m_y1 - 1 ); }

    [[nodiscard]] constexpr bool empty() const noexcept { return floating_point::greater( m_x1, m_x2 ) || floating_point::greater( m_y1, m_y2 ); }

    [[nodiscard]] constexpr bool valid() const noexcept { return floating_point::less( m_x1, m_x2, true ) && floating_point::less( m_y1, m_y2, true ); }

    [[nodiscard]] constexpr T left() const noexcept { return m_x1; }

    [[nodiscard]] constexpr T top() const noexcept { return m_y1; }

    [[nodiscard]] constexpr T right() const noexcept { return m_x2; }

    [[nodiscard]] constexpr T bottom() const noexcept { return m_y2; }

    [[nodiscard]] constexpr T x() const noexcept { return m_x1; }

    [[nodiscard]] constexpr T y() const noexcept { return m_y1; }

    [[nodiscard]] constexpr T width() const noexcept { return m_x2 - m_x1 + 1; }

    [[nodiscard]] constexpr T height() const noexcept { return m_y2 - m_y1 + 1; }

    inline void setLeft( T _pos ) noexcept { m_x1 = _pos; }

    inline void setTop( T _pos ) noexcept { m_y1 = _pos; }

    inline void setRight( T _pos ) noexcept { m_x2 = _pos; }

    inline void setBottom( T _pos ) noexcept { m_y2 = _pos; }

    inline void setWidth( T _width ) noexcept { m_x2 = m_x1 + _width - 1; }

    inline void setHeight( T _height ) noexcept { m_y2 = m_y2 + _height - 1; }

    [[nodiscard]] constexpr Rect<T> operator|( Rect<T> _rectangle ) const noexcept;
    [[nodiscard]] constexpr Rect<T> operator&( Rect<T> _rectangle ) const noexcept;
    [[nodiscard]] constexpr Rect<T> &operator|=( Rect<T> _rectangle ) noexcept;
    [[nodiscard]] constexpr Rect<T> &operator&=( Rect<T> _rectangle ) noexcept;

    [[nodiscard]] bool contains( Rect<T> _rectangle ) const noexcept;

    [[nodiscard]] constexpr Rect<T> intersected( Rect<T> _rectangle ) const noexcept { return *this & _rectangle; }

    [[nodiscard]] bool intersects( Rect<T> _rectangle ) const noexcept;

    [[nodiscard]] constexpr Rect<T> united( Rect<T> _rectangle ) const noexcept { return *this | _rectangle; }

    [[nodiscard]] static constexpr bool compareWidth( Rect<T> _rect1, Rect<T> _rect2 ) noexcept { return floating_point::less( _rect1.width(), _rect2.width() ); }

    [[nodiscard]] static constexpr bool compareHeight( Rect<T> _rect1, Rect<T> _rect2 ) noexcept { return floating_point::less( _rect1.height(), _rect2.height() ); }

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

  extern template bool Rect<int>::contains( Rect<int> _rectangle ) const noexcept;

  extern template bool Rect<float>::contains( Rect<float> _rectangle ) const noexcept;

  extern template bool Rect<double>::contains( Rect<double> _rectangle ) const noexcept;

  extern template bool Rect<int>::intersects( Rect<int> _rectangle ) const noexcept;

  extern template bool Rect<float>::intersects( Rect<float> _rectangle ) const noexcept;

  extern template bool Rect<double>::intersects( Rect<double> _rectangle ) const noexcept;
}
