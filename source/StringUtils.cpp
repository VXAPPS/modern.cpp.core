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
#include <cstring>

/* stl header */
#include <algorithm>

/* local header */
#include "StringUtils.h"

namespace vx::string_utils {

  constexpr auto trimmed = " \t\n\r\f\v";

  std::string &rightTrim( std::string &_string,
                          std::string_view _trim ) {

    _string.erase( _string.find_last_not_of( _trim.empty() ? trimmed : _trim ) + 1 );
    return _string;
  }

  std::string &leftTrim( std::string &_string,
                         std::string_view _trim ) {

    _string.erase( 0, _string.find_first_not_of( _trim.empty() ? trimmed : _trim ) );
    return _string;
  }

  std::string &trim( std::string &_string,
                     std::string_view _trim ) {

    return leftTrim( rightTrim( _string, _trim.empty() ? trimmed : _trim ), _trim.empty() ? trimmed : _trim );
  }

  bool startsWith( std::string_view _string,
                   std::string_view _start ) {

    return ( _string.rfind( _start, 0 ) == 0 );
  }

  bool endsWith( std::string_view _string,
                 std::string_view _end ) {

    if ( _string.length() >= _end.length() ) {

      return _string.compare( _string.length() - _end.length(), _end.length(), _end ) == 0;
    }
    return false;
  }

  constexpr bool BothAreSpaces( char lhs, char rhs ) { return ( lhs == rhs ) && ( lhs == ' ' ); }

  std::string simplified( std::string &_string ) {

    /* Replace every control with a space */
    std::replace( std::begin( _string ), std::end( _string ), '\t', ' ');
    std::replace( std::begin( _string ), std::end( _string ), '\n', ' ');
    std::replace( std::begin( _string ), std::end( _string ), '\r', ' ');
    std::replace( std::begin( _string ), std::end( _string ), '\f', ' ');
    std::replace( std::begin( _string ), std::end( _string ), '\v', ' ');

    /* Normalize spaces to just one */
    std::string::iterator new_end = std::unique( std::begin( _string ), std::end( _string ), BothAreSpaces);
    _string.erase( new_end, std::end( _string ) );

    /* Trim */
    trim( _string );

    return _string;
  }

  std::vector<std::string> tokenize( const std::string &_string,
                                     std::string_view _separator ) {

    std::vector<std::string> result {};
    std::string split = _string;
    std::size_t startPos = 0;
    std::size_t endPos = split.find( _separator );
    while ( endPos != std::string::npos ) {

      std::string word = split.substr( startPos, endPos - startPos );
      result.push_back( word );
      split = split.substr( endPos + _separator.length() );
      endPos = split.find( _separator );
    }
    result.push_back( split );
    return result;
  }

  std::string fromUnsignedChar( const unsigned char *_uchr,
                                std::size_t _size ) {

    std::size_t size = _size;
    if ( !size ) {

      size = strlen( reinterpret_cast<const char*>( _uchr ) );
    }
    return { _uchr, _uchr + size };
  }

#ifdef __APPLE__
  std::string fromCFStringRef( CFStringRef _stringRef ) {

    if ( const auto *fastCString = CFStringGetCStringPtr( _stringRef, kCFStringEncodingUTF8 ) ) {

      return std::string( fastCString );
    }

    auto utf16length = CFStringGetLength( _stringRef );
    auto maxUtf8len = CFStringGetMaximumSizeForEncoding( utf16length, kCFStringEncodingUTF8 );

    std::string converted( static_cast<std::size_t>( maxUtf8len ), '\0' );
    CFStringGetCString( _stringRef, converted.data(), maxUtf8len, kCFStringEncodingUTF8 );
    return converted;
  }
#endif
}
