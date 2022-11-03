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

/* modern.cpp.core */
#include <Line.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( Line, Simple_int32_t ) {

    Line line( Point( 5, 5 ), Point( 10, 10 ) );
    Line lineWithoutPoints( 5, 5, 5, 5 );
    const Line copy( Point( 10, 10 ), Point( 15, 15 ) );
    const Line initializer { 5, 5, 10, 10 };

    /* Null check */
    EXPECT_TRUE( lineWithoutPoints.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( line.x1() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.y1() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.x2() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.y2() ), typeid( std::int32_t ) );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5 );
    EXPECT_EQ( line.y1(), 5 );
    EXPECT_EQ( line.x2(), 10 );
    EXPECT_EQ( line.y2(), 10 );

    EXPECT_EQ( initializer.x1(), 5 );
    EXPECT_EQ( initializer.y1(), 5 );
    EXPECT_EQ( initializer.x2(), 10 );
    EXPECT_EQ( initializer.y2(), 10 );

    /* Distance */
    EXPECT_EQ( line.dx(), 5 );
    EXPECT_EQ( line.dy(), 5 );

    /* Type check from points */
    EXPECT_EQ( typeid( line.point1().x() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.point1().y() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.point2().x() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( line.point2().y() ), typeid( std::int32_t ) );

    /* Values from points */
    EXPECT_EQ( line.point1().x(), 5 );
    EXPECT_EQ( line.point1().y(), 5 );
    EXPECT_EQ( line.point2().x(), 10 );
    EXPECT_EQ( line.point2().y(), 10 );

    /* Calculated width */
    EXPECT_EQ( line.width(), 2 );

    /* Copy constructor */
    line = copy;

    /* Values direct */
    EXPECT_EQ( line.x1(), 10 );
    EXPECT_EQ( line.y1(), 10 );
    EXPECT_EQ( line.x2(), 15 );
    EXPECT_EQ( line.y2(), 15 );

    /* Move - no effect, it is a simple type, but is ist working? */
    line = std::move( lineWithoutPoints );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5 );
    EXPECT_EQ( line.y1(), 5 );
    EXPECT_EQ( line.x2(), 5 );
    EXPECT_EQ( line.y2(), 5 );
  }

  TEST( Line, Simple_float ) {

    Line line( Point( 5.4F, 5.4F ), Point( 10.4F, 10.4F ) );
    Line lineWithoutPoints( 5.4F, 5.4F, 5.4F, 5.4F );
    const Line copy( Point( 10.4F, 10.4F ), Point( 15.4F, 15.4F ) );
    const Line initializer { 5.4F, 5.4F, 10.4F, 10.4F };

    /* Null check */
    EXPECT_TRUE( lineWithoutPoints.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( line.x1() ), typeid( float ) );
    EXPECT_EQ( typeid( line.y1() ), typeid( float ) );
    EXPECT_EQ( typeid( line.x2() ), typeid( float ) );
    EXPECT_EQ( typeid( line.y2() ), typeid( float ) );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5.4F );
    EXPECT_EQ( line.y1(), 5.4F );
    EXPECT_EQ( line.x2(), 10.4F );
    EXPECT_EQ( line.y2(), 10.4F );

    EXPECT_EQ( initializer.x1(), 5.4F );
    EXPECT_EQ( initializer.y1(), 5.4F );
    EXPECT_EQ( initializer.x2(), 10.4F );
    EXPECT_EQ( initializer.y2(), 10.4F );

    /* Distance */
    EXPECT_EQ( line.dx(), 4.99999952F );
    EXPECT_EQ( line.dy(), 4.99999952F );

    /* Type check from points */
    EXPECT_EQ( typeid( line.point1().x() ), typeid( float ) );
    EXPECT_EQ( typeid( line.point1().y() ), typeid( float ) );
    EXPECT_EQ( typeid( line.point2().x() ), typeid( float ) );
    EXPECT_EQ( typeid( line.point2().y() ), typeid( float ) );

    /* Values from points */
    EXPECT_EQ( line.point1().x(), 5.4F );
    EXPECT_EQ( line.point1().y(), 5.4F );
    EXPECT_EQ( line.point2().x(), 10.4F );
    EXPECT_EQ( line.point2().y(), 10.4F );

    /* Calculated width */
    EXPECT_TRUE( floating_point::equal( static_cast<double>( line.width() ), static_cast<double>( 2.11474252F ) ) );

    /* Copy constructor */
    line = copy;

    /* Values direct */
    EXPECT_EQ( line.x1(), 10.4F );
    EXPECT_EQ( line.y1(), 10.4F );
    EXPECT_EQ( line.x2(), 15.4F );
    EXPECT_EQ( line.y2(), 15.4F );

    /* Move - no effect, it is a simple type, but is ist working? */
    line = std::move( lineWithoutPoints );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5.4F );
    EXPECT_EQ( line.y1(), 5.4F );
    EXPECT_EQ( line.x2(), 5.4F );
    EXPECT_EQ( line.y2(), 5.4F );
  }

  TEST( Line, Simple_double ) {

    Line line( Point( 5.5, 5.5 ), Point( 10.5, 10.5 ) );
    Line lineWithoutPoints( 5.5, 5.5, 5.5, 5.5 );
    const Line copy( Point( 10.5, 10.5 ), Point( 15.5, 15.5 ) );
    const Line initializer { 5.5, 5.5, 10.5, 10.5 };

    /* Null check */
    EXPECT_TRUE( lineWithoutPoints.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( line.x1() ), typeid( double ) );
    EXPECT_EQ( typeid( line.y1() ), typeid( double ) );
    EXPECT_EQ( typeid( line.x2() ), typeid( double ) );
    EXPECT_EQ( typeid( line.y2() ), typeid( double ) );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5.5 );
    EXPECT_EQ( line.y1(), 5.5 );
    EXPECT_EQ( line.x2(), 10.5 );
    EXPECT_EQ( line.y2(), 10.5 );

    EXPECT_EQ( initializer.x1(), 5.5 );
    EXPECT_EQ( initializer.y1(), 5.5 );
    EXPECT_EQ( initializer.x2(), 10.5 );
    EXPECT_EQ( initializer.y2(), 10.5 );

    /* Distance */
    EXPECT_EQ( line.dx(), 5. );
    EXPECT_EQ( line.dy(), 5. );

    /* Type check from points */
    EXPECT_EQ( typeid( line.point1().x() ), typeid( double ) );
    EXPECT_EQ( typeid( line.point1().y() ), typeid( double ) );
    EXPECT_EQ( typeid( line.point2().x() ), typeid( double ) );
    EXPECT_EQ( typeid( line.point2().y() ), typeid( double ) );

    /* Values from points */
    EXPECT_EQ( line.point1().x(), 5.5 );
    EXPECT_EQ( line.point1().y(), 5.5 );
    EXPECT_EQ( line.point2().x(), 10.5 );
    EXPECT_EQ( line.point2().y(), 10.5 );

    /* Calculated width */
    EXPECT_TRUE( floating_point::equal( line.width(), 2.1147425268811282 ) );

    /* Copy constructor */
    line = copy;

    /* Values direct */
    EXPECT_EQ( line.x1(), 10.5 );
    EXPECT_EQ( line.y1(), 10.5 );
    EXPECT_EQ( line.x2(), 15.5 );
    EXPECT_EQ( line.y2(), 15.5 );

    /* Move - no effect, it is a simple type, but is ist working? */
    line = std::move( lineWithoutPoints );

    /* Values direct */
    EXPECT_EQ( line.x1(), 5.5 );
    EXPECT_EQ( line.y1(), 5.5 );
    EXPECT_EQ( line.x2(), 5.5 );
    EXPECT_EQ( line.y2(), 5.5 );
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
