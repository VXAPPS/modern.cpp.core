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

/* stl header */
#include <list>
#include <optional>
#include <vector>

/* modern.cpp.core */
#include <Demangle.h>
#include <StringUtils.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( Demangle, Enum ) {

#ifndef _WIN32
    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    enum ColorUnscoped { RED = 2,
                         BLUE = 4,
                         GREEN = 8 };

    const std::vector<std::string_view> colorTokens { "vx", "Demangle_Enum_Test", "TestBody()", "Color" };
    const std::vector<std::string_view> colorUnscopedTokens { "vx", "Demangle_Enum_Test", "TestBody()", "ColorUnscoped" };

    const std::string result = demangleSimple( typeid( Color ).name() );
    const std::vector<std::string_view> colorTkens = string_utils::tokenize( result, "::" );
    EXPECT_EQ( colorTkens, colorTokens );

    const std::string resultColorUnscoped = demangleSimple( typeid( ColorUnscoped ).name() );
    const std::vector<std::string_view> colorUnscopedTkens = string_utils::tokenize( resultColorUnscoped, "::" );
    EXPECT_EQ( colorUnscopedTkens, colorUnscopedTokens );
#endif
  }

  TEST( Demangle, SimpleTypes ) {

    EXPECT_EQ( demangle( typeid( int ).name() ), "int" );
    EXPECT_EQ( demangle( typeid( float ).name() ), "float" );
    EXPECT_EQ( demangle( typeid( double ).name() ), "double" );
    EXPECT_EQ( demangleSimple( typeid( std::string ).name() ), "std::string" );
  }

  TEST( Demangle, ComplexTypes ) {

    EXPECT_EQ( demangleSimple( typeid( std::vector<int> ).name() ), "std::vector<int, std::allocator<int>>" );
  }

  TEST( DemangleExtreme, ComplexTypes ) {

    EXPECT_EQ( demangleExtreme( typeid( std::vector<int> ).name() ), "std::vector<int>" );
    EXPECT_EQ( demangleExtreme( typeid( std::set<int> ).name() ), "std::set<int>" );
    EXPECT_EQ( demangleExtreme( typeid( std::list<int> ).name() ), "std::list<int>" );
    EXPECT_EQ( demangleExtreme( typeid( std::optional<int> ).name() ), "std::optional<int>" );
    EXPECT_EQ( demangleExtreme( typeid( std::tuple<int, std::string, std::string_view> ).name() ), "std::tuple<int, std::string, std::string_view>" );
    EXPECT_EQ( demangleExtreme( typeid( std::tuple<int, char, int> ).name() ), "std::tuple<int, char, int>" );
    EXPECT_EQ( demangleExtreme( typeid( std::tuple<int, const char *, const char *> ).name() ), "std::tuple<int, const char *, const char *>" );

    const std::tuple tuple { 1, "abc", "def" };
    EXPECT_EQ( demangleExtreme( typeid( tuple ).name() ), "std::tuple<int, const char *, const char *>" );

    const std::tuple tuple2 { 1, 'a', "def" };
    EXPECT_EQ( demangleExtreme( typeid( tuple2 ).name() ), "std::tuple<int, char, const char *>" );
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

int main( int argc, char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
