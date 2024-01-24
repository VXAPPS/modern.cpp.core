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
#include <cstddef> // std::size_t
#include <cstdint> // std::int32_t
#include <cstdlib> // EXIT_SUCCESS

/* stl header */
#include <iostream>
#include <limits>
#include <utility> // std::pair

/* modern.cpp.core */
#include <FloatingPoint.h>

std::int32_t main() {

  bool result = false;

  constexpr std::size_t precisionTwo = 2;
  constexpr std::size_t precisionFive = 5;
  constexpr std::size_t precisionMax = std::numeric_limits<double>::digits10;

  constexpr double first = 1.23;
  constexpr double second = 2.2345678;
  constexpr double third = 2.2345678;
  constexpr double fourth = 2.2335678;

  std::cout.precision( precisionMax );

  std::cout << "Precision MAX: " << precisionMax << std::endl;

  /* equals */
  std::cout << "----- Equal" << std::endl;

  result = vx::floating_point::equal( first, second );
  std::cout << first << " == " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::equal( second, third );
  std::cout << second << " == " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::equal( third, fourth );
  std::cout << third << " == " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* less */
  std::cout << "----- Less" << std::endl;

  result = vx::floating_point::less( first, second );
  std::cout << first << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::less( second, third );
  std::cout << second << " < " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::less( third, fourth );
  std::cout << third << " < " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::less( first, second, true );
  std::cout << first << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::less( second, third, true );
  std::cout << second << " <= " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::less( third, fourth, true );
  std::cout << third << " <= " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* greater */
  std::cout << "----- Greater" << std::endl;

  result = vx::floating_point::greater( first, second );
  std::cout << first << " > " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::greater( second, third );
  std::cout << second << " > " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::greater( third, fourth );
  std::cout << third << " > " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::greater( first, second, true );
  std::cout << first << " >= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::greater( second, third, true );
  std::cout << second << " >= " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::greater( third, fourth, true );
  std::cout << third << " >= " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* between */
  std::cout << "----- Between" << std::endl;

  result = vx::floating_point::between( first, first, second );
  std::cout << first << " > " << first << " && " << first << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::between( second, first, second );
  std::cout << second << " > " << first << " && " << second << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::between( fourth, first, second );
  std::cout << fourth << " > " << first << " && " << fourth << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::between( first, first, second, true );
  std::cout << first << " >= " << first << " && " << first << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::between( second, first, second, true );
  std::cout << second << " >= " << first << " && " << second << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::floating_point::between( fourth, first, second, true );
  std::cout << fourth << " >= " << first << " && " << fourth << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* round */
  std::cout << "----- Round" << std::endl;

  double rounded = vx::floating_point::round( first, precisionTwo );
  std::cout << "round(2) " << first << " result: " << rounded << std::endl;

  rounded = vx::floating_point::round( second, precisionTwo );
  std::cout << "round(2) " << second << " result: " << rounded << std::endl;

  rounded = vx::floating_point::round( third, precisionFive );
  std::cout << "round(5) " << third << " result: " << rounded << std::endl;

  rounded = vx::floating_point::round( fourth, precisionFive );
  std::cout << "round(5) " << fourth << " result: " << rounded << std::endl;

  /* split */
  std::cout << "----- Split" << std::endl;

  std::pair<double, double> separated = vx::floating_point::split( first );
  std::cout << "split " << first << " result: " << separated.first << " " << separated.second << std::endl;

  separated = vx::floating_point::split( second );
  std::cout << "split " << second << " result: " << separated.first << " " << separated.second << std::endl;

  separated = vx::floating_point::split( third );
  std::cout << "split " << third << " result: " << separated.first << " " << separated.second << std::endl;

  separated = vx::floating_point::split( fourth );
  std::cout << "split " << fourth << " result: " << separated.first << " " << separated.second << std::endl;

  return EXIT_SUCCESS;
}
