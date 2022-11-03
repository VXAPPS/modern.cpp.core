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
#include <cstdint>

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
#include <Size.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( Size, Simple_int32_t ) {

    Size size( 5, 5 );
    Size size2( 5, 5 );
    const Size size3( 10, 10 );
    const Size sizeNull( 0, 0 );
    const Size copy( 15, 15 );
    const Size initializer { 10, 10 };

    /* Null check */
    EXPECT_FALSE( size.null() );
    EXPECT_TRUE( sizeNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( size.width() ), typeid( std::int32_t ) );
    EXPECT_EQ( typeid( size.height() ), typeid( std::int32_t ) );

    /* Setter */
    size.setWidth( 10 );
    size.setHeight( 10 );

    /* Values direct */
    EXPECT_EQ( size.width(), 10 );
    EXPECT_EQ( size.height(), 10 );
    EXPECT_EQ( size2.width(), 5 );
    EXPECT_EQ( size2.height(), 5 );

    EXPECT_EQ( copy.width(), 15 );
    EXPECT_EQ( copy.height(), 15 );
    EXPECT_EQ( initializer.width(), 10 );
    EXPECT_EQ( initializer.height(), 10 );

    /* comparision */
    EXPECT_TRUE( size == size3 );
    EXPECT_FALSE( size == size2 );
    EXPECT_FALSE( size == sizeNull );
    EXPECT_FALSE( !( size == size3 ) );
    EXPECT_TRUE( !( size == size2 ) );
    EXPECT_TRUE( !( size == sizeNull ) );

    /* operator */
    size += size2;
    EXPECT_EQ( size.width(), 15 );
    EXPECT_EQ( size.height(), 15 );

    size -= size2;
    EXPECT_EQ( size.width(), 10 );
    EXPECT_EQ( size.height(), 10 );

    /* Copy constructor */
    size = copy;

    /* Values direct */
    EXPECT_EQ( size.width(), 15 );
    EXPECT_EQ( size.height(), 15 );

    /* Move - no effect, it is a simple type, but is ist working? */
    size = std::move( size2 );

    /* Values direct */
    EXPECT_EQ( size.width(), 5 );
    EXPECT_EQ( size.height(), 5 );
  }

  TEST( Size, Simple_float ) {

    Size size( 5.4F, 5.4F );
    Size size2( 5.4F, 5.4F );
    const Size size3( 10.4F, 10.4F );
    const Size sizeNull( 0.F, 0.F );
    const Size copy( 15.4F, 15.4F );
    const Size initializer { 10.4F, 10.4F };

    /* Null check */
    EXPECT_FALSE( size.null() );
    EXPECT_TRUE( sizeNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( size.width() ), typeid( float ) );
    EXPECT_EQ( typeid( size.height() ), typeid( float ) );

    /* Setter */
    size.setWidth( 10.4F );
    size.setHeight( 10.4F );

    /* Values direct */
    EXPECT_EQ( size.width(), 10.4F );
    EXPECT_EQ( size.height(), 10.4F );
    EXPECT_EQ( size2.width(), 5.4F );
    EXPECT_EQ( size2.height(), 5.4F );

    EXPECT_EQ( copy.width(), 15.4F );
    EXPECT_EQ( copy.height(), 15.4F );
    EXPECT_EQ( initializer.width(), 10.4F );
    EXPECT_EQ( initializer.height(), 10.4F );

    /* comparision */
    EXPECT_TRUE( size == size3 );
    EXPECT_FALSE( size == size2 );
    EXPECT_FALSE( size == sizeNull );
    EXPECT_FALSE( !( size == size3 ) );
    EXPECT_TRUE( !( size == size2 ) );
    EXPECT_TRUE( !( size == sizeNull ) );

    /* operator */
    size += size2;
    EXPECT_EQ( size.width(), 15.7999992F );
    EXPECT_EQ( size.height(), 15.7999992F );

    size -= size2;
    EXPECT_EQ( size.width(), 10.4F );
    EXPECT_EQ( size.height(), 10.4F );

    /* Copy constructor */
    size = copy;

    /* Values direct */
    EXPECT_EQ( size.width(), 15.4F );
    EXPECT_EQ( size.height(), 15.4F );

    /* Move - no effect, it is a simple type, but is ist working? */
    size = std::move( size2 );

    /* Values direct */
    EXPECT_EQ( size.width(), 5.4F );
    EXPECT_EQ( size.height(), 5.4F );
  }

  TEST( Size, Simple_double ) {

    Size size( 5.5, 5.5 );
    Size size2( 5.5, 5.5 );
    const Size size3( 10.5, 10.5 );
    const Size sizeNull( 0., 0. );
    const Size copy( 15.5, 15.5 );
    const Size initializer { 10.5, 10.5 };

    /* Null check */
    EXPECT_FALSE( size.null() );
    EXPECT_TRUE( sizeNull.null() );

    /* Type check direct */
    EXPECT_EQ( typeid( size.width() ), typeid( double ) );
    EXPECT_EQ( typeid( size.height() ), typeid( double ) );

    /* Setter */
    size.setWidth( 10.5 );
    size.setHeight( 10.5 );

    /* Values direct */
    EXPECT_EQ( size.width(), 10.5 );
    EXPECT_EQ( size.height(), 10.5 );
    EXPECT_EQ( size2.width(), 5.5 );
    EXPECT_EQ( size2.height(), 5.5 );

    EXPECT_EQ( copy.width(), 15.5 );
    EXPECT_EQ( copy.height(), 15.5 );
    EXPECT_EQ( initializer.width(), 10.5 );
    EXPECT_EQ( initializer.height(), 10.5 );

    /* comparision */
    EXPECT_TRUE( size == size3 );
    EXPECT_FALSE( size == size2 );
    EXPECT_FALSE( size == sizeNull );
    EXPECT_FALSE( !( size == size3 ) );
    EXPECT_TRUE( !( size == size2 ) );
    EXPECT_TRUE( !( size == sizeNull ) );

    /* operator */
    size += size2;
    EXPECT_EQ( size.width(), 16. );
    EXPECT_EQ( size.height(), 16. );

    size -= size2;
    EXPECT_EQ( size.width(), 10.5 );
    EXPECT_EQ( size.height(), 10.5 );

    /* Copy constructor */
    size = copy;

    /* Values direct */
    EXPECT_EQ( size.width(), 15.5 );
    EXPECT_EQ( size.height(), 15.5 );

    /* Move - no effect, it is a simple type, but is ist working? */
    size = std::move( size2 );

    /* Values direct */
    EXPECT_EQ( size.width(), 5.5 );
    EXPECT_EQ( size.height(), 5.5 );
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
