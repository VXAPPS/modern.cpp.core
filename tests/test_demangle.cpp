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

/* stl header */
#include <list>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
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

#if defined _WIN32 && !defined _WIN64
    // TODO: Fix for 32bit version
    // bad, but we just need to drop that out on 32bit Windows.
#else
    using namespace std::literals;

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    enum ColorUnscoped { RED = 2, // NOSONAR just for testing purpose.
                         BLUE = 4,
                         GREEN = 8 };

    const std::vector colorTokens { "vx"sv, "Demangle_Enum_Test"sv, "TestBody()"sv, "Color"sv };
    const std::vector colorUnscopedTokens { "vx"sv, "Demangle_Enum_Test"sv, "TestBody()"sv, "ColorUnscoped"sv };

    const std::string result = demangle::simple( typeid( Color ).name() );
    const std::vector colorTkens = string_utils::tokenize( result, "::" );
    EXPECT_EQ( colorTkens, colorTokens );

    const std::string resultColorUnscoped = demangle::simple( typeid( ColorUnscoped ).name() );
    const std::vector colorUnscopedTkens = string_utils::tokenize( resultColorUnscoped, "::" );
    EXPECT_EQ( colorUnscopedTkens, colorUnscopedTokens );
#endif
  }

  TEST( Demangle, SimpleTypes ) {

    EXPECT_EQ( demangle::abi( typeid( std::uint8_t ).name() ), "unsigned char" );
    EXPECT_EQ( demangle::abi( typeid( std::int32_t ).name() ), "int" );
    EXPECT_EQ( demangle::abi( typeid( float ).name() ), "float" );
    EXPECT_EQ( demangle::abi( typeid( double ).name() ), "double" );
    EXPECT_EQ( demangle::simple( typeid( std::string ).name() ), "std::string" );
    EXPECT_EQ( demangle::simple( typeid( std::string_view ).name() ), "std::string_view" );
  }

  TEST( Demangle, ComplexTypes ) {

    EXPECT_EQ( demangle::simple( typeid( std::vector<int> ).name() ), "std::vector<int, std::allocator<int>>" );
    EXPECT_EQ( demangle::simple( typeid( std::set<int> ).name() ), "std::set<int, std::less<int>, std::allocator<int>>" );
    EXPECT_EQ( demangle::simple( typeid( std::list<int> ).name() ), "std::list<int, std::allocator<int>>" );
    EXPECT_EQ( demangle::simple( typeid( std::optional<int> ).name() ), "std::optional<int>" );
    EXPECT_EQ( demangle::simple( typeid( std::vector<std::string> ).name() ), "std::vector<std::string, std::allocator<std::string>>" );
    EXPECT_EQ( demangle::simple( typeid( std::vector<std::string_view> ).name() ), "std::vector<std::string_view, std::allocator<std::string_view>>" );
  }

  TEST( DemangleExtreme, ComplexTypes ) {

    EXPECT_EQ( demangle::extreme( typeid( std::vector<int> ).name() ), "std::vector<int>" );
    EXPECT_EQ( demangle::extreme( typeid( std::set<int> ).name() ), "std::set<int>" );
    EXPECT_EQ( demangle::extreme( typeid( std::list<int> ).name() ), "std::list<int>" );
    EXPECT_EQ( demangle::extreme( typeid( std::optional<int> ).name() ), "std::optional<int>" );
    EXPECT_EQ( demangle::extreme( typeid( std::vector<std::string> ).name() ), "std::vector<std::string>" );
    EXPECT_EQ( demangle::extreme( typeid( std::vector<std::string_view> ).name() ), "std::vector<std::string_view>" );
    EXPECT_EQ( demangle::extreme( typeid( std::tuple<int, std::string, std::string_view> ).name() ), "std::tuple<int, std::string, std::string_view>" );
    EXPECT_EQ( demangle::extreme( typeid( std::tuple<int, char, int> ).name() ), "std::tuple<int, char, int>" );
    EXPECT_EQ( demangle::extreme( typeid( std::tuple<int, const char *, const char *> ).name() ), "std::tuple<int, const char *, const char *>" );

    const std::tuple<int, const char *, const char *> tuple { 1, "abc", "def" };
    EXPECT_EQ( demangle::extreme( typeid( tuple ).name() ), "std::tuple<int, const char *, const char *>" );

    const std::tuple<int, char, const char *> tuple2 { 1, 'a', "def" };
    EXPECT_EQ( demangle::extreme( typeid( tuple2 ).name() ), "std::tuple<int, char, const char *>" );
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
