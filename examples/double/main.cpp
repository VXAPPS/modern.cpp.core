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

/* stl header */
#include <iostream>

/* modern.cpp.core header */
#include <Double.h>

int main() {

  bool result = false;

  double first = 1.23;
  double second = 2.2345678;
  double third = 2.2345678;
  double fourth = 2.2335678;

  std::cout.precision( 10 );

  /* equals */
  std::cout << "----- Equal" << std::endl;

  result = vx::doubleEqual( first, second );
  std::cout << first << " == " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleEqual( second, third );
  std::cout << second << " == " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleEqual( third, fourth );
  std::cout << third << " == " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* less */
  std::cout << "----- Less" << std::endl;

  result = vx::doubleLess( first, second );
  std::cout << first << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleLess( second, third );
  std::cout << second << " < " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleLess( third, fourth );
  std::cout << third << " < " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleLess( first, second, true );
  std::cout << first << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleLess( second, third, true );
  std::cout << second << " <= " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleLess( third, fourth, true );
  std::cout << third << " <= " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* greater */
  std::cout << "----- Greater" << std::endl;

  result = vx::doubleGreater( first, second );
  std::cout << first << " > " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleGreater( second, third );
  std::cout << second << " > " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleGreater( third, fourth );
  std::cout << third << " > " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleGreater( first, second, true );
  std::cout << first << " >= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleGreater( second, third, true );
  std::cout << second << " >= " << third << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleGreater( third, fourth, true );
  std::cout << third << " >= " << fourth << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* between */
  std::cout << "----- Between" << std::endl;

  result = vx::doubleBetween( first, first, second );
  std::cout << first << " > " << first << " && " << first << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleBetween( second, first, second );
  std::cout << second << " > " << first << " && " << second << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleBetween( fourth, first, second );
  std::cout << fourth << " > " << first << " && " << fourth << " < " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleBetween( first, first, second, true );
  std::cout << first << " >= " << first << " && " << first << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleBetween( second, first, second, true );
  std::cout << second << " >= " << first << " && " << second << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  result = vx::doubleBetween( fourth, first, second, true );
  std::cout << fourth << " >= " << first << " && " << fourth << " <= " << second << " result: " << std::boolalpha << result << std::noboolalpha << std::endl;

  /* round */
  std::cout << "----- Round" << std::endl;

  double rounded = 0.0;
  rounded = vx::doubleRound( first, 2 );
  std::cout << "round(2) " << first << " result: " << rounded << std::endl;

  rounded = vx::doubleRound( second, 2 );
  std::cout << "round(2) " << second << " result: " << rounded << std::endl;

  rounded = vx::doubleRound( third, 5 );
  std::cout << "round(5) " << third << " result: " << rounded << std::endl;

  rounded = vx::doubleRound( fourth, 5 );
  std::cout << "round(5) " << fourth << " result: " << rounded << std::endl;

  /* split */
  std::cout << "----- Split" << std::endl;

  std::pair<double, double> splited = {};
  splited = vx::doubleSplit( first );
  std::cout << "split " << first << " result: " << splited.first << " " << splited.second << std::endl;

  splited = vx::doubleSplit( second );
  std::cout << "split " << second << " result: " << splited.first << " " << splited.second << std::endl;

  splited = vx::doubleSplit( third );
  std::cout << "split " << third << " result: " << splited.first << " " << splited.second << std::endl;

  splited = vx::doubleSplit( fourth );
  std::cout << "split " << fourth << " result: " << splited.first << " " << splited.second << std::endl;

  return EXIT_SUCCESS;
}
