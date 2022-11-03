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
#include "FloatingPoint.h"
#include "TypeCheck.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template for size.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   * @tparam T   Type.
   */
  template <typename T>
  class Size : private TypeCheck<isVariantMember<T, std::variant<std::int32_t, float, double>>::value> {

  public:
    /**
     * @brief Default constructor for Size.
     */
    constexpr Size<T>() = default;

    /**
     * @brief Constructor for Size.
     * @param _width   Width value.
     * @param _height   Height value.
     */
    constexpr Size<T>( T _width,
                       T _height ) noexcept
      : m_width( _width ),
        m_height( _height ) {}

    [[nodiscard]] constexpr bool null() const noexcept { return floating_point::equal( m_width, static_cast<T>( 0 ) ) && floating_point::equal( m_height, static_cast<T>( 0 ) ); }

    [[nodiscard]] constexpr bool empty() const noexcept { return floating_point::less( m_width, static_cast<T>( 1 ) ) || floating_point::less( m_height, static_cast<T>( 1 ) ); }

    [[nodiscard]] constexpr T width() const noexcept { return m_width; }

    [[nodiscard]] constexpr T height() const noexcept { return m_height; }

    inline void setWidth( T _width ) noexcept { m_width = _width; }

    inline void setHeight( T _height ) noexcept { m_height = _height; }

    constexpr Size<T> &operator+=( Size<T> _size ) noexcept {

      m_width += _size.m_width;
      m_height += _size.m_height;
      return *this;
    }

    constexpr Size<T> &operator-=( Size<T> _size ) noexcept {

      m_width -= _size.m_width;
      m_height -= _size.m_height;
      return *this;
    }

    [[nodiscard]] constexpr bool operator==( Size<T> _size ) const noexcept { return floating_point::equal( m_width, _size.m_width ) && floating_point::equal( m_height, _size.m_height ); }

  private:
    /**
     * @brief Member for width.
     */
    T m_width = 1;

    /**
     * @brief Member for height.
     */
    T m_height = 1;
  };

  /**
   * @brief Template argument deduction.
   * @tparam T   Type.
   */
  template <typename T>
  Size( T ) -> Size<T>;
}
