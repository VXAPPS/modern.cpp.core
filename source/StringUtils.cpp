/*
 * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
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
#include <cctype> // std::isspace
#include <cstring>

/* stl header */
#include <algorithm>
#include <exception>
#include <functional>
#include <ios>
#include <iterator>
#include <optional>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

/* local header */
#include "Logger.h"
#include "StringUtils.h"

namespace std { // NOSONAR for std integration.

#if defined _MSC_VER && _MSC_VER < 1920
  using ::isspace;
  using ::tolower;
  using ::toupper;
#endif

#ifdef _WIN32
  using ::strnlen_s;
#else
  using ::strnlen;
#endif
}

namespace vx::string_utils {

  std::string &trimRight( std::string &_string,
                          std::string_view _trim ) noexcept {

    auto trimmed_ = [ &_trim ]( auto _chr ) {

      if ( !_trim.empty() ) {

        return _trim.find( _chr ) != std::string_view::npos;
      }
      return !std::isspace( static_cast<unsigned char>( _chr ) );
    };

    _string.erase( std::find_if( std::rbegin( _string ), std::rend( _string ), trimmed_ ).base(), _string.end() );
    return _string;
  }

  std::string &trimLeft( std::string &_string,
                         std::string_view _trim ) noexcept {

    auto trimmed_ = [ &_trim ]( auto _chr ) {

      if ( !_trim.empty() ) {

        return _trim.find( _chr ) != std::string_view::npos;
      }
      return !std::isspace( static_cast<unsigned char>( _chr ) );
    };

#if defined _MSC_VER || ( defined __GNUC__ && __GNUC__ >= 10 )
    _string.erase( _string.begin(), std::find_if( std::begin( _string ), std::end( _string ), trimmed_ ) );
#else
    _string.erase( _string.begin(), std::ranges::find_if( _string, trimmed_ ) );
#endif
    return _string;
  }

  std::string &trim( std::string &_string,
                     std::string_view _trim ) noexcept {

    return trimLeft( trimRight( _string, _trim ), _trim );
  }

  std::string &toLower( std::string &_string ) noexcept {

    std::ranges::transform( _string, std::begin( _string ), []( auto _chr ) { return static_cast<char>( std::tolower( _chr ) ); } );
    return _string;
  }

  std::string &toUpper( std::string &_string ) noexcept {

    std::ranges::transform( _string, std::begin( _string ), []( auto _chr ) { return static_cast<char>( std::toupper( _chr ) ); } );
    return _string;
  }

  bool startsWith( std::string_view _string,
                   std::string_view _start ) noexcept {

    return _string.rfind( _start, 0 ) == 0;
  }

  bool endsWith( std::string_view _string,
                 std::string_view _end ) noexcept {

    if ( _string.length() >= _end.length() ) {

      return _string.compare( _string.length() - _end.length(), _end.length(), _end ) == 0;
    }
    return false;
  }

  /**
   * @brief Check if left and right is space.
   * @param _left   Left character to check.
   * @param _right   Right character to check.
   * @return True, if left and right is a space - otherwise false.
   */
  constexpr bool bothAreSpaces( char _left,
                                char _right ) noexcept { return std::equal_to<> {}( _left, _right ) && std::equal_to<> {}( _left, ' ' ); }

  std::string &simplified( std::string &_string ) {

    /* Replace every control with a space */
    std::ranges::replace( _string, '\t', ' ' );
    std::ranges::replace( _string, '\n', ' ' );
    std::ranges::replace( _string, '\r', ' ' );
    std::ranges::replace( _string, '\f', ' ' );
    std::ranges::replace( _string, '\v', ' ' );

    /* Normalize spaces to just one */
    const auto newEnd = std::unique( std::begin( _string ), std::end( _string ), bothAreSpaces );
    _string.erase( newEnd, std::cend( _string ) );

    /* Trim */
    trim( _string );
    return _string;
  }

  std::vector<std::string_view> tokenize( std::string_view _string,
                                          std::string_view _separator,
                                          Split _split ) {

    std::vector<std::string_view> result {};
    std::string_view split = _string;
    std::size_t endPos = split.find( _separator );
    while ( endPos != std::string_view::npos ) {

      if ( const std::string_view word = split.substr( 0, endPos ); _split == Split::SkipEmpty && word.empty() ) {

        /* Nothing to do here */
      }
      else {

        result.push_back( word );
      }
      split = split.substr( endPos + _separator.length() );
      endPos = split.find( _separator );
    }

    if ( _split == Split::SkipEmpty && split.empty() ) {

      /* Nothing to do here */
    }
    else {

      result.push_back( split );
    }
    return result;
  }

  std::string toHex( std::string_view _string ) noexcept {

    std::ostringstream stream {};
    for ( auto chr : _string ) {

      stream << std::hex << static_cast<int>( chr );
    }

    std::string result {};
    try {

      result = stream.str();
    }
    catch ( const std::exception &_exception ) {

      logFatal() << _exception.what();
    }
    return result;
  }

  std::optional<std::string> fromUnsignedChar( const unsigned char *_uchr ) noexcept {

    /* nullptr check is mandatory */
    if ( !_uchr ) { return {}; }

    std::basic_string<unsigned char> string {};
    try {

      string = _uchr;
    }
    catch( const std::exception &_exception ) {

      logFatal() << _exception.what();
    }
    return std::make_optional<std::string>( std::cbegin( string ), std::cend( string ) );
  }

  std::optional<std::string> MAYBE_BAD_fromUnsignedChar( const unsigned char *_uchr,
                                                         std::size_t _size ) noexcept {

    /* nullptr check is mandatory */
    if ( !_uchr ) { return {}; }

    std::size_t size = _size;
    if ( !size ) {

#if defined __linux__ && defined __clang__ && __clang_major__ >= 18
      size = std::strlen( reinterpret_cast<const char *>( _uchr ) );
#else
      std::basic_string<unsigned char> string {};
      try {

        string = _uchr;
      }
      catch( const std::exception &_exception ) {

        logFatal() << _exception.what();
      }
  #ifdef _WIN32
      size = std::strnlen_s( reinterpret_cast<const char *>( _uchr ), string.size() ); // NOSONAR do not use reinterpret_cast.
  #else
      size = std::strnlen( reinterpret_cast<const char *>( _uchr ), string.size() ); // NOSONAR do not use reinterpret_cast.
  #endif
#endif
    }
    return std::make_optional<std::string>( _uchr, _uchr + size ); // NOSONAR do not use pointer arithmetic.
  }
}
