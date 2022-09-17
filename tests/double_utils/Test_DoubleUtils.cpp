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

/* cppunit header */
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Weverything"
#endif
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Weffc++"
#endif
#include <gtest/gtest.h>
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif
#ifdef __clang__
  #pragma clang diagnostic pop
#endif
using ::testing::InitGoogleTest;
using ::testing::Test;

/* modern.cpp.core */
#include <DoubleUtils.h>
#include <cmath>

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( DoubleUtils, Equal ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( double_utils::equal( first, second ) );
    EXPECT_TRUE( double_utils::equal( second, third ) );
    EXPECT_FALSE( double_utils::equal( third, fourth ) );
  }

  TEST( DoubleUtils, Less ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_TRUE( double_utils::less( first, second ) );
    EXPECT_FALSE( double_utils::less( second, third ) );
    EXPECT_FALSE( double_utils::less( third, fourth ) );
    EXPECT_TRUE( double_utils::less( first, second, true ) );
    EXPECT_TRUE( double_utils::less( second, third, true ) );
    EXPECT_FALSE( double_utils::less( third, fourth, true ) );
  }

  TEST( DoubleUtils, Greater ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( double_utils::greater( first, second ) );
    EXPECT_FALSE( double_utils::greater( second, third ) );
    EXPECT_TRUE( double_utils::greater( third, fourth ) );
    EXPECT_FALSE( double_utils::greater( first, second, true ) );
    EXPECT_TRUE( double_utils::greater( second, third, true ) );
    EXPECT_TRUE( double_utils::greater( third, fourth, true ) );
  }

  TEST( DoubleUtils, Between ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_FALSE( double_utils::between( first, first, second ) );
    EXPECT_FALSE( double_utils::between( second, first, second ) );
    EXPECT_TRUE( double_utils::between( fourth, first, second ) );
    EXPECT_TRUE( double_utils::between( first, first, second, true ) );
    EXPECT_TRUE( double_utils::between( second, first, second, true ) );
    EXPECT_TRUE( double_utils::between( fourth, first, second, true ) );
  }

  TEST( DoubleUtils, Round ) {

    constexpr std::size_t precisionTwo = 2;
    constexpr std::size_t precisionFive = 5;

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    EXPECT_EQ( double_utils::round( first, precisionTwo ), 1.23 );
    EXPECT_EQ( double_utils::round( second, precisionTwo ), 2.23 );
    EXPECT_EQ( double_utils::round( third, precisionFive ), 2.23457 );
    EXPECT_EQ( double_utils::round( fourth, precisionFive ), 2.23357 );
  }

  TEST( DoubleUtils, Split ) {

    constexpr double first = 1.23;
    constexpr double second = 2.2345678;
    constexpr double third = 2.2345678;
    constexpr double fourth = 2.2335678;

    std::pair<double, double> splitted = vx::double_utils::split( first );
    EXPECT_EQ( splitted.first, 1.0 );
    EXPECT_TRUE( double_utils::equal( splitted.second, 0.23 ) );

    splitted = vx::double_utils::split( second );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( double_utils::equal( splitted.second, 0.2345678 ) );

    splitted = vx::double_utils::split( third );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( double_utils::equal( splitted.second, 0.2345678 ) );

    splitted = vx::double_utils::split( fourth );
    EXPECT_EQ( splitted.first, 2.0 );
    EXPECT_TRUE( double_utils::equal( splitted.second, 0.2335678 ) );
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

int main( int argc, char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
