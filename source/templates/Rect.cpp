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

/* stl header */
#include <algorithm>

/* local header */
#include "Rect.h"

namespace vx {

  template <typename T>
  constexpr Rect<T> Rect<T>::operator|( Rect<T> _rectangle ) const noexcept {

    if ( null() ) {

      return _rectangle;
    }
    if ( _rectangle.null() ) {

      return *this;
    }

    T l1 = m_x1;
    T r1 = m_x1;
    if ( m_x2 - m_x1 + 1 < 0 ) {

      l1 = m_x2;
    }
    else {

      r1 = m_x2;
    }

    T l2 = _rectangle.m_x1;
    T r2 = _rectangle.m_x1;
    if ( _rectangle.m_x2 - _rectangle.m_x1 + 1 < 0 ) {

      l2 = _rectangle.m_x2;
    }
    else {

      r2 = _rectangle.m_x2;
    }

    T t1 = m_y1;
    T b1 = m_y1;
    if ( m_y2 - m_y1 + 1 < 0 ) {

      t1 = m_y2;
    }
    else {

      b1 = m_y2;
    }

    T t2 = _rectangle.m_y1;
    T b2 = _rectangle.m_y1;
    if ( _rectangle.m_y2 - _rectangle.m_y1 + 1 < 0 ) {

      t2 = _rectangle.m_y2;
    }
    else {

      b2 = _rectangle.m_y2;
    }

    Rect result {};
    result.m_x1 = std::min( l1, l2 );
    result.m_x2 = std::max( r1, r2 );
    result.m_y1 = std::min( t1, t2 );
    result.m_y2 = std::max( b1, b2 );
    return result;
  }

  template <typename T>
  constexpr Rect<T> Rect<T>::operator&( Rect<T> _rectangle ) const noexcept {

    if ( null() || _rectangle.null() ) {

      return {};
    }

    T l1 = m_x1;
    T r1 = m_x1;
    if ( m_x2 - m_x1 + 1 < 0 ) {

      l1 = m_x2;
    }
    else {

      r1 = m_x2;
    }

    T l2 = _rectangle.m_x1;
    T r2 = _rectangle.m_x1;
    if ( _rectangle.m_x2 - _rectangle.m_x1 + 1 < 0 ) {

      l2 = _rectangle.m_x2;
    }
    else {

      r2 = _rectangle.m_x2;
    }

    if ( l1 > r2 || l2 > r1 ) {

      return {};
    }

    T t1 = m_y1;
    T b1 = m_y1;
    if ( m_y2 - m_y1 + 1 < 0 ) {

      t1 = m_y2;
    }
    else {

      b1 = m_y2;
    }

    T t2 = _rectangle.m_y1;
    T b2 = _rectangle.m_y1;
    if ( _rectangle.m_y2 - _rectangle.m_y1 + 1 < 0 ) {

      t2 = _rectangle.m_y2;
    }
    else {

      b2 = _rectangle.m_y2;
    }

    if ( t1 > b2 || t2 > b1 ) {

      return {};
    }

    Rect result {};
    result.m_x1 = std::max( l1, l2 );
    result.m_x2 = std::min( r1, r2 );
    result.m_y1 = std::max( t1, t2 );
    result.m_y2 = std::min( b1, b2 );
    return result;
  }

  template <typename T>
  bool Rect<T>::contains( Rect<T> _rectangle ) const noexcept {

    if ( null() || _rectangle.null() ) {

      return false;
    }

    T l1 = m_x1;
    T r1 = m_x1;
    if ( m_x2 - m_x1 + 1 < 0 ) {

      l1 = m_x2;
    }
    else {

      r1 = m_x2;
    }

    T l2 = _rectangle.m_x1;
    T r2 = _rectangle.m_x1;
    if ( _rectangle.m_x2 - _rectangle.m_x1 + 1 < 0 ) {

      l2 = _rectangle.m_x2;
    }
    else {

      r2 = _rectangle.m_x2;
    }

    if ( l2 < l1 || r2 > r1 ) {

      return false;
    }

    T t1 = m_y1;
    T b1 = m_y1;
    if ( m_y2 - m_y1 + 1 < 0 ) {

      t1 = m_y2;
    }
    else {

      b1 = m_y2;
    }

    T t2 = _rectangle.m_y1;
    T b2 = _rectangle.m_y1;
    if ( _rectangle.m_y2 - _rectangle.m_y1 + 1 < 0 ) {

      t2 = _rectangle.m_y2;
    }
    else {

      b2 = _rectangle.m_y2;
    }

    return !( t2 < t1 || b2 > b1 );
  }

  template bool Rect<int>::contains( Rect<int> ) const noexcept;

  template bool Rect<float>::contains( Rect<float> ) const noexcept;

  template bool Rect<double>::contains( Rect<double> ) const noexcept;

  template <typename T>
  bool Rect<T>::intersects( Rect<T> _rectangle ) const noexcept {

    if ( null() || _rectangle.null() ) {

      return false;
    }

    T l1 = m_x1;
    T r1 = m_x1;
    if ( m_x2 - m_x1 + 1 < 0 ) {

      l1 = m_x2;
    }
    else {

      r1 = m_x2;
    }

    T l2 = _rectangle.m_x1;
    T r2 = _rectangle.m_x1;
    if ( _rectangle.m_x2 - _rectangle.m_x1 + 1 < 0 ) {

      l2 = _rectangle.m_x2;
    }
    else {

      r2 = _rectangle.m_x2;
    }

    if ( l1 > r2 || l2 > r1 ) {

      return false;
    }

    T t1 = m_y1;
    T b1 = m_y1;
    if ( m_y2 - m_y1 + 1 < 0 ) {

      t1 = m_y2;
    }
    else {

      b1 = m_y2;
    }

    T t2 = _rectangle.m_y1;
    T b2 = _rectangle.m_y1;
    if ( _rectangle.m_y2 - _rectangle.m_y1 + 1 < 0 ) {

      t2 = _rectangle.m_y2;
    }
    else {

      b2 = _rectangle.m_y2;
    }

    return !( t1 > b2 || t2 > b1 );
  }

  template bool Rect<int>::intersects( Rect<int> ) const noexcept;

  template bool Rect<float>::intersects( Rect<float> ) const noexcept;

  template bool Rect<double>::intersects( Rect<double> ) const noexcept;
}
