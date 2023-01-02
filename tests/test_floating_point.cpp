/*
 * Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
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
#include <cstdint> // std::int32_t

/* gtest header */
#include <gtest/gtest.h>

/* modern.cpp.core */
#include <FloatingPoint.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( FloatingPoint, Equal ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( floating_point::equal( first, second ) );
    EXPECT_TRUE( floating_point::equal( second, third ) );
    EXPECT_FALSE( floating_point::equal( third, fourth ) );
  }

  TEST( FloatingPoint, Less ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_TRUE( floating_point::less( first, second ) );
    EXPECT_FALSE( floating_point::less( second, third ) );
    EXPECT_FALSE( floating_point::less( third, fourth ) );
    EXPECT_TRUE( floating_point::less( first, second, true ) );
    EXPECT_TRUE( floating_point::less( second, third, true ) );
    EXPECT_FALSE( floating_point::less( third, fourth, true ) );
  }

  TEST( FloatingPoint, Greater ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( floating_point::greater( first, second ) );
    EXPECT_FALSE( floating_point::greater( second, third ) );
    EXPECT_TRUE( floating_point::greater( third, fourth ) );
    EXPECT_FALSE( floating_point::greater( first, second, true ) );
    EXPECT_TRUE( floating_point::greater( second, third, true ) );
    EXPECT_TRUE( floating_point::greater( third, fourth, true ) );
  }

  TEST( FloatingPoint, Between ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( floating_point::between( first, first, second ) );
    EXPECT_FALSE( floating_point::between( second, first, second ) );
    EXPECT_TRUE( floating_point::between( fourth, first, second ) );
    EXPECT_TRUE( floating_point::between( first, first, second, true ) );
    EXPECT_TRUE( floating_point::between( second, first, second, true ) );
    EXPECT_TRUE( floating_point::between( fourth, first, second, true ) );
  }

  TEST( FloatingPoint, Round ) {

    constexpr std::size_t precisionTwo = 2;
    constexpr std::size_t precisionFive = 5;

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_EQ( floating_point::round( first, precisionTwo ), 1.23 );
    EXPECT_EQ( floating_point::round( second, precisionTwo ), 2.23 );
    EXPECT_EQ( floating_point::round( third, precisionFive ), 2.23457 );
    EXPECT_EQ( floating_point::round( fourth, precisionFive ), 2.23357 );
  }

  TEST( FloatingPoint, Split ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    std::pair<double, double> splitted = vx::floating_point::split( first );
    EXPECT_EQ( splitted.first, 1.0 );
    EXPECT_TRUE( floating_point::equal( splitted.second, 0.23 ) );

    splitted = vx::floating_point::split( second );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( floating_point::equal( splitted.second, 0.2345678 ) );

    splitted = vx::floating_point::split( third );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( floating_point::equal( splitted.second, 0.2345678 ) );

    splitted = vx::floating_point::split( fourth );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( floating_point::equal( splitted.second, 0.2335678 ) );
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

std::int32_t main( std::int32_t argc,
                   char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
