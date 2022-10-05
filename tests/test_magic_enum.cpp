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
#include <numeric>

/* magic enum */
#include <magic_enum.hpp>

/* modern.cpp.core */
#include "Cpp23.h"

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( MagicEnum, EnumString ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    std::string_view colorRed = magic_enum::enum_name( Color::RED );
    EXPECT_EQ( colorRed, "RED" );

    std::string_view colorBlue = magic_enum::enum_name( Color::BLUE );
    EXPECT_EQ( colorBlue, "BLUE" );

    std::string_view colorGreen = magic_enum::enum_name( Color::GREEN );
    EXPECT_EQ( colorGreen, "GREEN" );
  }

  TEST( MagicEnum, StringEnum ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    std::optional colorRed = magic_enum::enum_cast<Color>( "RED" );
    EXPECT_TRUE( colorRed.has_value() );
    EXPECT_EQ( colorRed.value(), Color::RED );

    std::optional colorBlue = magic_enum::enum_cast<Color>( "BLUE" );
    EXPECT_TRUE( colorBlue.has_value() );
    EXPECT_EQ( colorBlue.value(), Color::BLUE );

    std::optional colorGreen = magic_enum::enum_cast<Color>( "GREEN" );
    EXPECT_TRUE( colorGreen.has_value() );
    EXPECT_EQ( colorGreen.value(), Color::GREEN );

    /* Bad case */
    std::optional colorPurple = magic_enum::enum_cast<Color>( "PURPLE" );
    EXPECT_FALSE( colorPurple.has_value() );
  }

  TEST( MagicEnum, IntegerEnum ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    std::optional colorRed = magic_enum::enum_cast<Color>( 2 );
    EXPECT_TRUE( colorRed.has_value() );
    EXPECT_EQ( colorRed.value(), Color::RED );

    std::optional colorBlue = magic_enum::enum_cast<Color>( 4 );
    EXPECT_TRUE( colorBlue.has_value() );
    EXPECT_EQ( colorBlue.value(), Color::BLUE );

    std::optional colorGreen = magic_enum::enum_cast<Color>( 8 );
    EXPECT_TRUE( colorGreen.has_value() );
    EXPECT_EQ( colorGreen.value(), Color::GREEN );

    /* Bad case */
    /* any value */
    /* BUG: https://github.com/Neargye/magic_enum/issues/216 */
    std::optional colorUnkown = magic_enum::enum_cast<Color>( 7 );
    EXPECT_TRUE( colorUnkown.has_value() );

    constexpr auto colors = magic_enum::enum_values<Color>();

    auto calcEnum = []( auto value, Color color ) {
      return value + std::to_underlying( color );
    };

    auto max = std::accumulate( std::begin( colors ), std::end( colors ), 0, calcEnum );
    EXPECT_EQ( max, 14 );

    std::optional colorMax = magic_enum::enum_cast<Color>( max );
    EXPECT_TRUE( colorMax.has_value() );

    std::optional colorMaxPlusOne = magic_enum::enum_cast<Color>( max + 1 );
    EXPECT_FALSE( colorMaxPlusOne.has_value() );
  }

  TEST( MagicEnum, IndexAccess ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    Color colorRed = magic_enum::enum_value<Color>( 0 );
    EXPECT_EQ( colorRed, Color::RED );

    Color colorBlue = magic_enum::enum_value<Color>( 1 );
    EXPECT_EQ( colorBlue, Color::BLUE );

    Color colorGreen = magic_enum::enum_value<Color>( 2 );
    EXPECT_EQ( colorGreen, Color::GREEN );

    /* Bad case */
    /* Will assert, but would be better if this could not compile with static_assert... */
    /* but static_assert is not possible while index is not a integral_constant */
    // Color colorUnkown = magic_enum::enum_value<Color>(3);
  }

  TEST( MagicEnum, Values ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    constexpr auto colors = magic_enum::enum_values<Color>();
    std::array<Color, 3> check { Color::RED, Color::BLUE, Color::GREEN };
    EXPECT_EQ( colors, check );
  }

  TEST( MagicEnum, Count ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    constexpr std::size_t colorCount = magic_enum::enum_count<Color>();
    EXPECT_EQ( colorCount, 3U );
  }

  TEST( MagicEnum, ValueInteger ) {

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    auto colorRed = magic_enum::enum_integer( Color::RED );
    EXPECT_EQ( colorRed, 2 );
    EXPECT_EQ( colorRed, std::to_underlying( Color::RED ) );

    auto colorBlue = magic_enum::enum_integer( Color::BLUE );
    EXPECT_EQ( colorBlue, 4 );
    EXPECT_EQ( colorBlue, std::to_underlying( Color::BLUE ) );

    auto colorGreen = magic_enum::enum_integer( Color::GREEN );
    EXPECT_EQ( colorGreen, 8 );
    EXPECT_EQ( colorGreen, std::to_underlying( Color::GREEN ) );
  }

  TEST( MagicEnum, Underlaying ) {

    using namespace std::literals;

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    auto colorRed = magic_enum::enum_integer( Color::RED );
    EXPECT_EQ( typeid( colorRed ), typeid( int ) );
    EXPECT_EQ( typeid( std::underlying_type<Color>::type ), typeid( int ) );

    enum class ColorUnsigned : unsigned { RED = 2,
                                          BLUE = 4,
                                          GREEN = 8 };

    auto colorRedUnsigned = magic_enum::enum_integer( ColorUnsigned::RED );
    EXPECT_EQ( typeid( colorRedUnsigned ), typeid( unsigned int ) );
    EXPECT_EQ( typeid( std::underlying_type<ColorUnsigned>::type ), typeid( unsigned int ) );

    enum class ColorChar : char { RED = 'a',
                                  BLUE = 'b',
                                  GREEN = 'c' };

    auto colorRedChar = magic_enum::enum_integer( ColorChar::RED );
    EXPECT_EQ( typeid( colorRedChar ), typeid( char ) );
    EXPECT_EQ( typeid( std::underlying_type<ColorChar>::type ), typeid( char ) );
  }

  TEST( MagicEnum, Names ) {

    using namespace std::literals;

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    constexpr auto names = magic_enum::enum_names<Color>();
    std::array<std::string_view, 3> check { "RED"sv, "BLUE"sv, "GREEN"sv };
    EXPECT_EQ( names, check );
  }

  TEST( MagicEnum, Entries ) {

    using namespace std::literals;

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    constexpr auto entries = magic_enum::enum_entries<Color>();
    std::array<std::pair<Color, std::string_view>, 3> check { { { Color::RED, "RED"sv }, { Color::BLUE, "BLUE"sv }, { Color::GREEN, "GREEN"sv } } };
    EXPECT_EQ( entries, check );
  }

  TEST( MagicEnum, Flags ) {

    using namespace magic_enum::bitwise_operators;

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    Color colors = Color::RED | Color::GREEN;
    EXPECT_EQ( std::to_underlying( colors ), 10 );

    /* or */
    EXPECT_EQ( std::to_underlying( Color::RED | Color::BLUE ), 6 );
    EXPECT_EQ( std::to_underlying( Color::BLUE | Color::GREEN ), 12 );
    EXPECT_EQ( std::to_underlying( Color::GREEN | Color::BLUE ), 12 );
    EXPECT_EQ( std::to_underlying( Color::BLUE | Color::RED ), 6 );
    EXPECT_EQ( std::to_underlying( Color::RED | Color::BLUE | Color::GREEN ), 14 );

    /* contains */
    EXPECT_EQ( std::to_underlying( colors & Color::RED ), 2 );
    EXPECT_EQ( std::to_underlying( colors & Color::GREEN ), 8 );
    EXPECT_EQ( std::to_underlying( colors & Color::BLUE ), 0 );

    EXPECT_TRUE( std::to_underlying( colors & Color::RED ) );
    EXPECT_TRUE( std::to_underlying( colors & Color::GREEN ) );
    EXPECT_FALSE( std::to_underlying( colors & Color::BLUE ) );

    /* xor */
    EXPECT_EQ( std::to_underlying( Color::RED ^ Color::BLUE ), 6 );
    EXPECT_EQ( std::to_underlying( Color::BLUE ^ Color::GREEN ), 12 );
    EXPECT_EQ( std::to_underlying( Color::GREEN ^ Color::BLUE ), 12 );
    EXPECT_EQ( std::to_underlying( Color::BLUE ^ Color::RED ), 6 );

    /* and not */
    EXPECT_EQ( std::to_underlying( colors & ~Color::RED ), 8 );
    EXPECT_EQ( std::to_underlying( colors & ~Color::GREEN ), 2 );
    EXPECT_EQ( std::to_underlying( colors & ~Color::BLUE ), 10 );

    /* or not */
    EXPECT_EQ( std::to_underlying( colors | ~Color::RED ), -1 );
    EXPECT_EQ( std::to_underlying( colors | ~Color::GREEN ), -1 );
    EXPECT_EQ( std::to_underlying( colors | ~Color::BLUE ), -5 );

    /* xor not */
    EXPECT_EQ( std::to_underlying( colors ^ ~Color::RED ), -9 );
    EXPECT_EQ( std::to_underlying( colors ^ ~Color::GREEN ), -3 );
    EXPECT_EQ( std::to_underlying( colors ^ ~Color::BLUE ), -15 );
  }

  TEST( MagicEnum, Checks ) {

    enum ColorUnscoped { RED = 2,
                         BLUE = 4,
                         GREEN = 8 };

    enum class Color { RED = 2,
                       BLUE = 4,
                       GREEN = 8 };

    EXPECT_TRUE( magic_enum::is_unscoped_enum<ColorUnscoped>::value );
    EXPECT_TRUE( magic_enum::is_unscoped_enum_v<ColorUnscoped> );

    EXPECT_FALSE( magic_enum::is_unscoped_enum<Color>::value );
    EXPECT_FALSE( magic_enum::is_unscoped_enum_v<Color> );

    // EXPECT_FALSE( magic_enum::is_unscoped_enum<int> ); - not compileable - seems correct.
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

int main( int argc, char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
