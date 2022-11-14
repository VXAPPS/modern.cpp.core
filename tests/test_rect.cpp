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

/* gtest header */
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
#include <Rect.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( Rect, SimpleInt ) {

    Rect rect( 5, 5, 10, 10 );
    Rect rect2( 6, 6, 8, 8 );
    const Rect rect3( 5, 5, 10, 10 );
    const Rect rectNull( 0, 0, 0, 0 );
    const Rect copy( 5, 5, 15, 15 );
    const Rect initializer { 5, 5, 10, 10 };

    /* Null check */
    EXPECT_FALSE( rect.null() );
    EXPECT_TRUE( rectNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( rect.x() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( rect.y() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( rect.width() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( rect.height() ), typeid( std::int32_t ) );

    /* Setter */
    rect.setLeft( 5 );
    rect.setTop( 5 );

    /* Values direct */
    EXPECT_EQ( rect.x(), 5 );
    EXPECT_EQ( rect.y(), 5 );
    EXPECT_EQ( rect.width(), 10 );
    EXPECT_EQ( rect.height(), 10 );
    EXPECT_EQ( rect2.x(), 6 );
    EXPECT_EQ( rect2.y(), 6 );
    EXPECT_EQ( rect2.width(), 8 );
    EXPECT_EQ( rect2.height(), 8 );

    EXPECT_EQ( copy.x(), 5 );
    EXPECT_EQ( copy.y(), 5 );
    EXPECT_EQ( copy.width(), 15 );
    EXPECT_EQ( copy.height(), 15 );
    EXPECT_EQ( initializer.x(), 5 );
    EXPECT_EQ( initializer.y(), 5 );
    EXPECT_EQ( initializer.width(), 10 );
    EXPECT_EQ( initializer.height(), 10 );

    /* comparision */
    EXPECT_TRUE( rect == rect3 );
    EXPECT_FALSE( rect == rect2 );
    EXPECT_FALSE( rect == rectNull );
    EXPECT_FALSE( !( rect == rect3 ) );
    EXPECT_TRUE( !( rect == rect2 ) );
    EXPECT_TRUE( !( rect == rectNull ) );

    /* operator */
    EXPECT_TRUE( rect.contains( rect2 ) );
    EXPECT_FALSE( rect2.contains( rect ) );
    EXPECT_TRUE( rect3.contains( rect ) );
    EXPECT_TRUE( copy.intersects( rect ) );
    EXPECT_TRUE( rect.intersects( copy ) );
    EXPECT_FALSE( rect.intersects( rectNull ) );

    /* Copy constructor */
    rect = copy;

    /* Values direct */
    EXPECT_EQ( rect.x(), 5 );
    EXPECT_EQ( rect.y(), 5 );
    EXPECT_EQ( rect.width(), 15 );
    EXPECT_EQ( rect.height(), 15 );

    /* Move - no effect, it is a simple type, but is ist working? */
    rect = std::move( rect2 );

    /* Values direct */
    EXPECT_EQ( rect.x(), 6 );
    EXPECT_EQ( rect.y(), 6 );
    EXPECT_EQ( rect.width(), 8 );
    EXPECT_EQ( rect.height(), 8 );
  }

  TEST( Rect, SimpleFloat ) {

    Rect rect( 5.4F, 5.4F, 10.4F, 10.4F );
    Rect rect2( 6.4F, 6.4F, 8.4F, 8.4F );
    const Rect rect3( 5.4F, 5.4F, 10.4F, 10.4F );
    const Rect rectNull( 0.F, 0.F, 0.F, 0.F );
    const Rect copy( 5.4F, 5.4F, 15.4F, 15.4F );
    const Rect initializer { 5.4F, 5.4F, 10.4F, 10.4F };

    /* Null check */
    EXPECT_FALSE( rect.null() );
    EXPECT_TRUE( rectNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( rect.x() ), typeid( float ) );
    EXPECT_EQ( typeid( rect.y() ), typeid( float ) );
    EXPECT_EQ( typeid( rect.width() ), typeid( float ) );
    EXPECT_EQ( typeid( rect.height() ), typeid( float ) );

    /* Setter */
    rect.setLeft( 5.4F );
    rect.setTop( 5.4F );

    /* Values direct */
    EXPECT_EQ( rect.x(), 5.4F );
    EXPECT_EQ( rect.y(), 5.4F );
    EXPECT_EQ( rect.width(), 10.4F );
    EXPECT_EQ( rect.height(), 10.4F );
    EXPECT_EQ( rect2.x(), 6.4F );
    EXPECT_EQ( rect2.y(), 6.4F );
    EXPECT_EQ( rect2.width(), 8.4F );
    EXPECT_EQ( rect2.height(), 8.4F );

    EXPECT_EQ( copy.x(), 5.4F );
    EXPECT_EQ( copy.y(), 5.4F );
    EXPECT_EQ( copy.width(), 15.4F );
    EXPECT_EQ( copy.height(), 15.4F );
    EXPECT_EQ( initializer.x(), 5.4F );
    EXPECT_EQ( initializer.y(), 5.4F );
    EXPECT_EQ( initializer.width(), 10.4F );
    EXPECT_EQ( initializer.height(), 10.4F );

    /* comparision */
    EXPECT_TRUE( rect == rect3 );
    EXPECT_FALSE( rect == rect2 );
    EXPECT_FALSE( rect == rectNull );
    EXPECT_FALSE( !( rect == rect3 ) );
    EXPECT_TRUE( !( rect == rect2 ) );
    EXPECT_TRUE( !( rect == rectNull ) );

    /* operator */
    EXPECT_TRUE( rect.contains( rect2 ) );
    EXPECT_FALSE( rect2.contains( rect ) );
    EXPECT_TRUE( rect3.contains( rect ) );
    EXPECT_TRUE( copy.intersects( rect ) );
    EXPECT_TRUE( rect.intersects( copy ) );
    EXPECT_FALSE( rect.intersects( rectNull ) );

    /* Copy constructor */
    rect = copy;

    /* Values direct */
    EXPECT_EQ( rect.x(), 5.4F );
    EXPECT_EQ( rect.y(), 5.4F );
    EXPECT_EQ( rect.width(), 15.4F );
    EXPECT_EQ( rect.height(), 15.4F );

    /* Move - no effect, it is a simple type, but is ist working? */
    rect = std::move( rect2 );

    /* Values direct */
    EXPECT_EQ( rect.x(), 6.4F );
    EXPECT_EQ( rect.y(), 6.4F );
    EXPECT_EQ( rect.width(), 8.4F );
    EXPECT_EQ( rect.height(), 8.4F );
  }

  TEST( Rect, SimpleDouble ) {

    Rect rect( 5.5, 5.5, 10.5, 10.5 );
    Rect rect2( 6.5, 6.5, 8.5, 8.5 );
    const Rect rect3( 5.5, 5.5, 10.5, 10.5 );
    const Rect rectNull( 0., 0., 0., 0. );
    const Rect copy( 5.5, 5.5, 15.5, 15.5 );
    const Rect initializer { 5.5, 5.5, 10.5, 10.5 };

    /* Null check */
    EXPECT_FALSE( rect.null() );
    EXPECT_TRUE( rectNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( rect.x() ), typeid( double ) );
    EXPECT_EQ( typeid( rect.y() ), typeid( double ) );
    EXPECT_EQ( typeid( rect.width() ), typeid( double ) );
    EXPECT_EQ( typeid( rect.height() ), typeid( double ) );

    /* Setter */
    rect.setLeft( 5.5 );
    rect.setTop( 5.5 );

    /* Values direct */
    EXPECT_EQ( rect.x(), 5.5 );
    EXPECT_EQ( rect.y(), 5.5 );
    EXPECT_EQ( rect.width(), 10.5 );
    EXPECT_EQ( rect.height(), 10.5 );
    EXPECT_EQ( rect2.x(), 6.5 );
    EXPECT_EQ( rect2.y(), 6.5 );
    EXPECT_EQ( rect2.width(), 8.5 );
    EXPECT_EQ( rect2.height(), 8.5 );

    EXPECT_EQ( copy.x(), 5.5 );
    EXPECT_EQ( copy.y(), 5.5 );
    EXPECT_EQ( copy.width(), 15.5 );
    EXPECT_EQ( copy.height(), 15.5 );
    EXPECT_EQ( initializer.x(), 5.5 );
    EXPECT_EQ( initializer.y(), 5.5 );
    EXPECT_EQ( initializer.width(), 10.5 );
    EXPECT_EQ( initializer.height(), 10.5 );

    /* comparision */
    EXPECT_TRUE( rect == rect3 );
    EXPECT_FALSE( rect == rect2 );
    EXPECT_FALSE( rect == rectNull );
    EXPECT_FALSE( !( rect == rect3 ) );
    EXPECT_TRUE( !( rect == rect2 ) );
    EXPECT_TRUE( !( rect == rectNull ) );

    /* operator */
    EXPECT_TRUE( rect.contains( rect2 ) );
    EXPECT_FALSE( rect2.contains( rect ) );
    EXPECT_TRUE( rect3.contains( rect ) );
    EXPECT_TRUE( copy.intersects( rect ) );
    EXPECT_TRUE( rect.intersects( copy ) );
    EXPECT_FALSE( rect.intersects( rectNull ) );

    /* Copy constructor */
    rect = copy;

    /* Values direct */
    EXPECT_EQ( rect.x(), 5.5 );
    EXPECT_EQ( rect.y(), 5.5 );
    EXPECT_EQ( rect.width(), 15.5 );
    EXPECT_EQ( rect.height(), 15.5 );

    /* Move - no effect, it is a simple type, but is ist working? */
    rect = std::move( rect2 );

    /* Values direct */
    EXPECT_EQ( rect.x(), 6.5 );
    EXPECT_EQ( rect.y(), 6.5 );
    EXPECT_EQ( rect.width(), 8.5 );
    EXPECT_EQ( rect.height(), 8.5 );
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
