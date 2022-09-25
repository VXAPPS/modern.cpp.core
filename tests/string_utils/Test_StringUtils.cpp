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
#include <StringUtils.h>

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( StringUtils, TrimLeft ) {

    std::string source = "   The answer is 42.   ";
    EXPECT_EQ( string_utils::trimLeft( source ), "The answer is 42.   " );
    EXPECT_EQ( source, "The answer is 42.   " );
  }

  TEST( StringUtils, TrimRight ) {

    std::string source = "   The answer is 42.   ";
    EXPECT_EQ( string_utils::trimRight( source ), "   The answer is 42." );
    EXPECT_EQ( source, "   The answer is 42." );
  }

  TEST( StringUtils, Trim ) {

    std::string source = "   The answer is 42.   ";
    EXPECT_EQ( string_utils::trim( source ), "The answer is 42." );
    EXPECT_EQ( source, "The answer is 42." );
  }

  TEST( StringUtils, StartsWith ) {

    std::string source = "The answer is 42.";
    EXPECT_FALSE( string_utils::startsWith( source, "abc" ) );
    EXPECT_FALSE( string_utils::startsWith( source, "the" ) );
    EXPECT_TRUE( string_utils::startsWith( source, "The" ) );
    EXPECT_TRUE( string_utils::startsWith( source, "T" ) );

    /* pineapple in japanese. Painappuro in romanji. */
    source = "パイナップル";
    EXPECT_TRUE( string_utils::startsWith( source, "パイ" ) );
    EXPECT_FALSE( string_utils::startsWith( source, "Anan" ) );
    EXPECT_FALSE( string_utils::startsWith( source, "Pain" ) );
  }

  TEST( StringUtils, EndsWith ) {

    std::string source = "The answer is 42.";
    EXPECT_FALSE( string_utils::endsWith( source, "xyz." ) );
    EXPECT_FALSE( string_utils::endsWith( source, "is fourty-two." ) );
    EXPECT_TRUE( string_utils::endsWith( source, "is 42." ) );
    EXPECT_TRUE( string_utils::endsWith( source, "2." ) );

    /* pineapple in japanese. Painappuro in romanji. */
    source = "パイナップル";
    EXPECT_TRUE( string_utils::endsWith( source, "プル" ) );
    EXPECT_FALSE( string_utils::endsWith( source, "anas" ) );
    EXPECT_FALSE( string_utils::endsWith( source, "puro" ) );
  }

  TEST( StringUtils, Simplified ) {

    std::string source = "   The   answer   is   42.   ";
    EXPECT_EQ( string_utils::simplified( source ), "The answer is 42." );
    EXPECT_EQ( source, "The answer is 42." );
  }

  TEST( StringUtils, Tokenize ) {

    std::string source = "The answer is 42.";
    std::vector<std::string_view> tokenized = string_utils::tokenize( source, " " );
    std::vector<std::string_view> expected = { "The", "answer", "is", "42." };
    EXPECT_EQ( tokenized.size(), expected.size() );
    EXPECT_EQ( tokenized, expected );

    source = " The answer is 42. ";
    tokenized = string_utils::tokenize( source, " ", string_utils::Split::SkipEmpty );
    EXPECT_EQ( tokenized.size(), expected.size() );
    EXPECT_EQ( tokenized, expected );

    tokenized = string_utils::tokenize( source, " ", string_utils::Split::KeepEmpty );
    expected = { "", "The", "answer", "is", "42.", "" };
    EXPECT_EQ( tokenized.size(), expected.size() );
    EXPECT_EQ( tokenized, expected );
  }

  TEST( StringUtils, FromUnsignedChar ) {

    unsigned char chrArray[] = "The answer is 42.";
    const unsigned char *chrPointer = chrArray;
    EXPECT_EQ( string_utils::fromUnsignedChar( chrPointer ), "The answer is 42." );
    EXPECT_EQ( string_utils::fromUnsignedChar( chrPointer, 0 ), "The answer is 42." );
    EXPECT_EQ( string_utils::fromUnsignedChar( chrPointer, 17 ), "The answer is 42." );
    EXPECT_EQ( string_utils::fromUnsignedChar( chrPointer, 10 ), "The answer" );
    EXPECT_NE( string_utils::fromUnsignedChar( chrPointer, 5 ), "The answer is 42." );
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

int main( int argc, char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
