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

/* imagr header */
#include <Point.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( Point, Simple_int ) {

    Point point( 5, 5 );
    Point point2( 5, 5 );
    const Point point3( 10, 10 );
    const Point pointNull( 0, 0 );
    const Point copy( 15, 15 );
    const Point initializer { 10, 10 };

    /* Null check */
    EXPECT_FALSE( point.null() );
    EXPECT_TRUE( pointNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( point.x() ), typeid( int ) );
    EXPECT_EQ( typeid( point.y() ), typeid( int ) );

    /* Setter */
    point.setX( 10 );
    point.setY( 10 );

    /* Values direct */
    EXPECT_EQ( point.x(), 10 );
    EXPECT_EQ( point.y(), 10 );
    EXPECT_EQ( point2.x(), 5 );
    EXPECT_EQ( point2.y(), 5 );

    EXPECT_EQ( copy.x(), 15 );
    EXPECT_EQ( copy.y(), 15 );
    EXPECT_EQ( initializer.x(), 10 );
    EXPECT_EQ( initializer.y(), 10 );

    /* Manhatten Length */
    EXPECT_EQ( point.manhattanLength(), 20 );
    EXPECT_EQ( point2.manhattanLength(), 10 );

    /* comparision */
    EXPECT_TRUE( point == point3 );
    EXPECT_FALSE( point == point2 );
    EXPECT_FALSE( point == pointNull );
    EXPECT_FALSE( point != point3 );
    EXPECT_TRUE( point != point2 );
    EXPECT_TRUE( point != pointNull );

    /* operator */
    point += point2;
    EXPECT_EQ( point.x(), 15 );
    EXPECT_EQ( point.y(), 15 );

    point -= point2;
    EXPECT_EQ( point.x(), 10 );
    EXPECT_EQ( point.y(), 10 );

    /* Copy constructor */
    point = copy;

    /* Values direct */
    EXPECT_EQ( point.x(), 15 );
    EXPECT_EQ( point.y(), 15 );

    /* Move - no effect, it is a simple type, but is ist working? */
    point = std::move( point2 );

    /* Values direct */
    EXPECT_EQ( point.x(), 5 );
    EXPECT_EQ( point.y(), 5 );
  }

  TEST( Point, Simple_float ) {

    Point point( 5.4F, 5.4F );
    Point point2( 5.4F, 5.4F );
    const Point point3( 10.4F, 10.4F );
    const Point pointNull( 0.F, 0.F );
    const Point copy( 15.4F, 15.4F );
    const Point initializer { 10.4F, 10.4F };

    /* Null check */
    EXPECT_FALSE( point.null() );
    EXPECT_TRUE( pointNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( point.x() ), typeid( float ) );
    EXPECT_EQ( typeid( point.y() ), typeid( float ) );

    /* Setter */
    point.setX( 10.4F );
    point.setY( 10.4F );

    /* Values direct */
    EXPECT_EQ( point.x(), 10.4F );
    EXPECT_EQ( point.y(), 10.4F );
    EXPECT_EQ( point2.x(), 5.4F );
    EXPECT_EQ( point2.y(), 5.4F );

    EXPECT_EQ( copy.x(), 15.4F );
    EXPECT_EQ( copy.y(), 15.4F );
    EXPECT_EQ( initializer.x(), 10.4F );
    EXPECT_EQ( initializer.y(), 10.4F );

    /* Manhatten Length */
    EXPECT_EQ( point.manhattanLength(), 20.8F );
    EXPECT_EQ( point2.manhattanLength(), 10.8F );

    /* comparision */
    EXPECT_TRUE( point == point3 );
    EXPECT_FALSE( point == point2 );
    EXPECT_FALSE( point == pointNull );
    EXPECT_FALSE( point != point3 );
    EXPECT_TRUE( point != point2 );
    EXPECT_TRUE( point != pointNull );

    /* operator */
    point += point2;
    EXPECT_EQ( point.x(), 15.7999992F );
    EXPECT_EQ( point.y(), 15.7999992F );

    point -= point2;
    EXPECT_EQ( point.x(), 10.4F );
    EXPECT_EQ( point.y(), 10.4F );

    /* Copy constructor */
    point = copy;

    /* Values direct */
    EXPECT_EQ( point.x(), 15.4F );
    EXPECT_EQ( point.y(), 15.4F );

    /* Move - no effect, it is a simple type, but is ist working? */
    point = std::move( point2 );

    /* Values direct */
    EXPECT_EQ( point.x(), 5.4F );
    EXPECT_EQ( point.y(), 5.4F );
  }

  TEST( Point, Simple_double ) {

    Point point( 5.5, 5.5 );
    Point point2( 5.5, 5.5 );
    const Point point3( 10.5, 10.5 );
    const Point pointNull( 0., 0. );
    const Point copy( 15.5, 15.5 );
    const Point initializer { 10.5, 10.5 };

    /* Null check */
    EXPECT_FALSE( point.null() );
    EXPECT_TRUE( pointNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( point.x() ), typeid( double ) );
    EXPECT_EQ( typeid( point.y() ), typeid( double ) );

    /* Setter */
    point.setX( 10.5 );
    point.setY( 10.5 );

    /* Values direct */
    EXPECT_EQ( point.x(), 10.5 );
    EXPECT_EQ( point.y(), 10.5 );
    EXPECT_EQ( point2.x(), 5.5 );
    EXPECT_EQ( point2.y(), 5.5 );

    EXPECT_EQ( copy.x(), 15.5 );
    EXPECT_EQ( copy.y(), 15.5 );
    EXPECT_EQ( initializer.x(), 10.5 );
    EXPECT_EQ( initializer.y(), 10.5 );

    /* Manhatten Length */
    EXPECT_EQ( point.manhattanLength(), 21. );
    EXPECT_EQ( point2.manhattanLength(), 11. );

    /* comparision */
    EXPECT_TRUE( point == point3 );
    EXPECT_FALSE( point == point2 );
    EXPECT_FALSE( point == pointNull );
    EXPECT_FALSE( point != point3 );
    EXPECT_TRUE( point != point2 );
    EXPECT_TRUE( point != pointNull );

    /* operator */
    point += point2;
    EXPECT_EQ( point.x(), 16. );
    EXPECT_EQ( point.y(), 16. );

    point -= point2;
    EXPECT_EQ( point.x(), 10.5 );
    EXPECT_EQ( point.y(), 10.5 );

    /* Copy constructor */
    point = copy;

    /* Values direct */
    EXPECT_EQ( point.x(), 15.5 );
    EXPECT_EQ( point.y(), 15.5 );

    /* Move - no effect, it is a simple type, but is ist working? */
    point = std::move( point2 );

    /* Values direct */
    EXPECT_EQ( point.x(), 5.5 );
    EXPECT_EQ( point.y(), 5.5 );
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

int main( int argc, char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
