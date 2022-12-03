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

/* c header */
#include <cmath>   // std::abs, std::floor, std::modf, std::pow
#include <cstddef> // std::size_t

/* stl header */
#include <algorithm>
#include <utility>

/**
 * @brief vx (VX APPS) floating_point namespace.
 */
namespace vx::floating_point {

  /**
   * @brief The Equal enum.
   */
  enum class Equal {

    Absolute, /**< Absolute value. */
    Relative, /**< Relative value. */
    Combined  /**< Absolute and relative value. */
  };

  /**
   * @brief Is _left and _right equal?
   * @tparam T   Type.
   * @param _left   The first value.
   * @param _right   The second value.
   * @param _equal   Absolute or relative to input or combined.
   * @return True, if _left and _right are equal - otherwise false.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] constexpr bool equal( T _left,
                                      T _right,
                                      Equal _equal = Equal::Absolute ) noexcept {

    /* Absolute */
    auto factor = static_cast<T>( 1 );
    if ( _equal == Equal::Relative ) {

      factor = std::max<T>( std::abs( _left ), std::abs( _right ) );
    }
    else if ( _equal == Equal::Combined ) {

      factor = std::max<T>( factor, std::max<T>( std::abs( _left ), std::abs( _right ) ) );
    }
    return std::abs( _left - _right ) <= std::numeric_limits<T>::epsilon() * factor;
  }

  /**
   * @brief Is _left less than _right or _orEqual?
   * @tparam T   Type.
   * @param _left   The first value.
   * @param _right   The second value.
   * @param _orEqual   Check if _left and _right are equal - default false.
   * @param _equal   Absolute or relative to input or combined.
   * @return True, if _left is less than _right or _left and _right are equal and
   * _orEqual is set to true - otherwise false.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] constexpr bool less( T _left,
                                     T _right,
                                     bool _orEqual = false,
                                     Equal _equal = Equal::Absolute ) noexcept {

    if ( equal( _left, _right, _equal ) ) {

      return _orEqual;
    }
    return _left < _right;
  }

  /**
   * @brief Is _left greater than _right or _orEqual?
   * @tparam T   Type.
   * @param _left   The first value.
   * @param _right   The second value.
   * @param _orEqual   Check if _left and _right are equal - default false.
   * @param _equal   Absolute or relative to input or combined.
   * @return True, if _left is greater than _right or _left and _right are equal and
   * _orEqual is set to true - otherwise false.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] constexpr bool greater( T _left,
                                        T _right,
                                        bool _orEqual = false,
                                        Equal _equal = Equal::Absolute ) noexcept {

    if ( equal( _left, _right, _equal ) ) {

      return _orEqual;
    }
    return _left > _right;
  }

  /**
   * @brief Is _value between _min and _max or _orEqual.
   * @tparam T   Type.
   * @param _value   Value to test.
   * @param _min   Is _value greater?
   * @param _max   Is _value less?
   * @param _orEqual  Is _value == _min or _value == _max
   * @param _equal   Absolute or relative to input or combined.
   * @return True, if _value is between _min and _max _orEqual - otherwise false.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] constexpr bool between( T _value,
                                        T _min,
                                        T _max,
                                        bool _orEqual = false,
                                        Equal _equal = Equal::Absolute ) noexcept {

    return greater( _value, _min, _orEqual, _equal ) && less( _value, _max, _orEqual, _equal );
  }

  /** @brief Base for default precision factor. */
  constexpr double precisionBase = 10;

  /** @brief Base for rounding. */
  constexpr double roundBase = 0.5;

  /**
   * @brief Round a double _value by _precision. Rounded by default to two decimal places.
   * @tparam T   Type.
   * @param _value   Value to round.
   * @param _precision   Decimal places to round.
   * @return The rounded value.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] constexpr T round( T _value,
                                   std::size_t _precision = 2 ) noexcept {

    const auto factor = _precision != 0 ? std::pow( precisionBase, _precision ) : 1;
    return std::floor( _value * factor + roundBase ) / factor;
  }

  /**
   * @brief Split a double _value to its integer and decimal places.
   * @tparam T   Type.
   * @param _value   Value to split.
   * @return The integer and decimal places.
   */
  template <typename T>
  // requires std::is_floating_point_v<T>
  [[nodiscard]] std::pair<T, T> split( T _value ) noexcept {

    T integral = 0.0;
    const auto fraction = std::modf( _value, &integral );
    return std::make_pair( integral, fraction );
  }
}
