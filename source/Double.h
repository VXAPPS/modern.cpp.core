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

/**
 * @brief VX (VX Apps) Namespace.
 */
namespace VX {

  /**
   * @brief Is _left and _right equal? Rounded by default to second places.
   * @param _left   The first value.
   * @param _right   The second value.
   * @return True, if _left and _right are equal - otherwise false.
   */
  bool doubleEquals( double _left,
                     double _right );

  /**
   * @brief Is _left less _right or _orEqual? Rounded by default to second places.
   * @param _left   The first value.
   * @param _right   The second value.
   * @param _orEqual   Check if _left and _right are equal - default false.
   * @return True, if _left less _right or _left and _right are equal and
   * _orEqual is set to true - otherwise false.
   */
  bool doubleLess( double _left,
                   double _right,
                   bool _orEqual = false );

  /**
   * @brief Is _left greater _right or _orEqual? Rounded by default to second places.
   * @param _left   The first value.
   * @param _right   The second value.
   * @param _orEqual   Check if _left and _right are equal - default false.
   * @return True, if _left greater _right or _left and _right are equal and
   * _orEqual is set to true - otherwise false.
   */
  bool doubleGreater( double _left,
                      double _right,
                      bool _orEqual = false );

  /**
   * @brief Is _value between _min and _max or _orEqual.
   * @param _value   Value to test.
   * @param _min   Is _value greater?
   * @param _max   Is _value less?
   * @param _orEqual  Is _value == _min or _value == _max
   * @return True, if _value is between _min and _max _orEqual - otherwise false.
   */
  bool doubleBetween( double _value,
                      double _min,
                      double _max,
                      bool _orEqual = false );

  /**
   * @brief Round a double _value by _places.
   * @param _value   Value to round.
   * @param _places   Places to round.
   * @return The rounded value.
   */
  double doubleRound( double _value,
                      std::size_t _places = 2 );
}