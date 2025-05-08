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
#include <cstdlib> // EXIT_SUCCESS

/* stl header */
#include <any>
#include <array>
#include <chrono>
#include <format>
#include <iostream>
#include <list>
#include <map>
#include <memory> // std::unique_ptr
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <utility> // std::pair
#include <variant>
#include <vector>

/* magic enum */
#include <magic_enum/magic_enum.hpp>

/* modern.cpp.core */
#include <Logger.h>
#include <Logger_any.h>
#include <Logger_enum.h>

using namespace std::literals;

class MyClass {

public:
  explicit MyClass( std::string_view _something )
    : m_something( _something ) {}

  void test() const { std::cout << m_something << std::endl; }

  friend std::ostream &operator<<( std::ostream &out, MyClass val ) {

    out << val.m_something;
    return out;
  }

  friend vx::logger::Logger &operator<<( vx::logger::Logger &_debug, MyClass _vec ) {

    _debug.stream() << _vec;
    return _debug;
  }

private:
  std::string_view m_something {};
};

std::int32_t main() {

  vx::logger::Configuration::instance().setAvoidLogBelow( vx::logger::Severity::Verbose );

  using namespace std::literals;

  constexpr std::int32_t aInt = 17;
  constexpr std::int32_t bInt = 12;
  constexpr double magic = 1.123;
  const std::string test = "blub";
  const char *chr = "test_chr";

  logInfo() << "test" << bInt << test << 1U << magic << chr;
  vx::logger::Logger() << "test2" << aInt;

  const std::vector vec { "abc"s, "def"s, "ghj"s };
  logVerbose() << vec;

  const std::string *str = nullptr;
  logDebug() << str << false << true << nullptr << 'a';

  const auto blub = std::make_unique<std::string>( "blub2"s );
  logInfo() << "Pointer:" << blub.get();

  const std::list list { "abc"s, "def"s, "ghj"s };
  logWarning() << list;

  const std::map<std::int32_t, std::string> map { { 3, "abc"s }, { 1, "def"s }, { 2, "ghj"s } };
  logError() << map;

  const std::unordered_map<std::int32_t, std::string_view> umap { { 3, "abc"sv }, { 1, "def"sv }, { 2, "ghj"sv } };
  logFatal() << umap;

  const std::tuple tuple { 1, "abc"s, "def"sv };
  logInfo() << tuple;

  const std::tuple<int, const char *, const char *> tuple2 { 1, "abc", "def" };
  logInfo() << tuple2;

  logVerbose() << std::make_pair( 1, "hello" );

  logDebug() << std::make_any<std::int32_t>( 1 ) << std::make_any<double>( 1.234 ) << std::make_any<std::string>( "hello" );

  const std::any blubAny = 1;
  const std::any helo = std::make_any<std::string>( "hello" );
  logDebug() << blubAny << helo << std::make_any<std::vector<int>>( { 1, 2, 3, 4 } );

  const std::unordered_map<std::int32_t, std::string_view> testsv { { 2, "ghj"sv }, { 1, "def"sv }, { 3, "abc"sv } };
  std::ignore = testsv;

  logInfo() << MyClass( "Blub" );

  std::vector<std::any> anyList {};
  anyList.emplace_back( std::make_any<std::string>( "hello" ) );
  anyList.emplace_back( std::make_any<std::vector<int>>( { 1, 2, 3, 4 } ) );
  logWarning() << anyList;

  const std::set<std::int32_t> set { 1, 2, 3, 3 };
  logError() << set;

  constexpr double magicArr1 = 1.23;
  constexpr double magicArr2 = 1.24;
  constexpr double magicArr3 = 1.25;
  constexpr double magicArr4 = 1.26;

  const std::array arr { magicArr1, magicArr2, magicArr3, magicArr4 };
  logFatal() << arr;

  const std::variant<std::int32_t, double> variant { magicArr3 };
  logInfo() << variant;

  constexpr std::int32_t theAnswerOfEverything = 42;
  logFatal() << std::format( "The answer is {}."sv, theAnswerOfEverything );

  constexpr double someDouble = 4.2;

  const std::tuple tupl { theAnswerOfEverything, 'a', someDouble }; // Another C++17 feature: class template argument deduction
  std::apply( []( auto &&...args ) { logDebug() << std::forward_as_tuple( args... ); }, tupl );

  constexpr const auto &severities = magic_enum::enum_entries<vx::logger::Path>();
  logFatal() << severities;
  for ( const auto &[ key, value ] : severities ) {

    logFatal() << key << value;
  }
  logDebug() << magic_enum::enum_name( vx::logger::Path::Filename ) << vx::logger::Path::Filename;

  constexpr const auto &severityNames = magic_enum::enum_names<vx::logger::Path>();
  logInfo() << severityNames;

  enum class Path {

    Filename,
    Complete,
    Absolute
  };

  constexpr const auto &pathNames = magic_enum::enum_entries<Path>();
  logInfo() << pathNames;

  logInfo().stream() << std::format( "int: {0:d}; hex: {0:#x}; oct: {0:#o}; bin: {0:#b}"sv, theAnswerOfEverything );

  const std::optional opti = "myOptional"s;
  const std::optional<std::string> optiNull = std::nullopt;
  logInfo() << opti << optiNull << std::make_optional<std::vector<char>>( { 'a', 'b', 'c' } );

  logInfo() << 2h;
  logInfo() << 10min;
  logInfo() << 5s;
  logInfo() << 100ms;
  logInfo() << 100us;
  logInfo() << 100ns;

  const auto now = std::chrono::system_clock::now();
  const auto nowAsTimeT = std::chrono::system_clock::to_time_t( now );
  logInfo() << nowAsTimeT;

  const auto nowMilli = std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ) % 1000;
  logInfo() << nowMilli;

  logInfo() << Path::Absolute;

  return EXIT_SUCCESS;
}
