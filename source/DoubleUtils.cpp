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

/* c header */
#include <cmath> // std::fabs, std::floor, std::modf, std::pow

/* stl header */
#include <algorithm>

/* local header */
#include "DoubleUtils.h"

namespace vx::double_utils {

  /** Base for default precision factor. */
  constexpr double precisionBase = 10;

  /** Base for rounding. */
  constexpr double roundBase = 0.5;

  bool equal( double _left,
              double _right,
              Equal _equal ) noexcept {

    /* Absolute */
    double factor = 1.0;
    if ( _equal == Equal::Relative ) {

      factor = std::max( std::fabs( _left ) , std::fabs( _right ) ) ;
    }
    else if ( _equal == Equal::Combined ) {

      factor = std::max( { 1.0, std::fabs( _left ) , std::fabs( _right ) } ) ;
    }
    return std::fabs( _left - _right ) <= std::numeric_limits<double>::epsilon() * factor;
  }

  bool less( double _left,
             double _right,
             bool _orEqual,
             Equal _equal ) noexcept {

    if ( equal( _left, _right, _equal ) ) {

      return _orEqual;
    }
    return _left < _right;
  }

  bool greater( double _left,
                double _right,
                bool _orEqual,
                Equal _equal ) noexcept {

    if ( equal( _left, _right, _equal ) ) {

      return _orEqual;
    }
    return _left > _right;
  }

  bool between( double _value,
                double _min,
                double _max,
                bool _orEqual,
                Equal _equal ) noexcept {

    return greater( _value, _min, _orEqual, _equal ) && less( _value, _max, _orEqual, _equal );
  }

  double round( double _value,
                std::size_t _precision ) noexcept {

    const double factor = _precision != 0 ? std::pow( precisionBase, _precision ) : 1;
    return std::floor( _value * factor + roundBase ) / factor;
  }

  std::pair<double, double> split( double _value ) noexcept {

    double integral = 0.0;
    const double fraction = std::modf( _value, &integral );
    return std::make_pair( integral, fraction );
  }
}
