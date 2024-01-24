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
#include <cstddef> // std::size_t
#include <cstdint> // std::int8_t
#include <ctime> // std::time

/* stl header */
#include <algorithm>
#include <iomanip>
#include <iostream> // std::streambuf, std::cout
#include <source_location.hpp>
#include <string>
#include <string_view>
#include <sstream>

/* magic enum */
#include <magic_enum.hpp>

/* local header */
#include "Logger.h"
#include "StringUtils.h"
#include "Timestamp.h"

namespace vx::logger {

  using timestamp::Precision;

#ifdef _WIN32
  class WindowsBuffer : public std::stringbuf {

  public:
    virtual std::int32_t sync() override {

      return 0;
    }
  };
#endif

  Logger::Logger( Severity _severity,
                  const std::source_location &_location )
    : m_severity( _severity ),
      m_location( _location ),
#ifdef _WIN32
      m_stream( new WindowsBuffer() ) {
#else
      m_stream( {} ) {
#endif

    if ( Configuration::instance().avoidLogBelow() > _severity ) {

      return;
    }

    if ( _severity >= Severity::Error ) {

      m_stream.rdbuf( std::cerr.rdbuf() );
    }
    else {

      m_stream.rdbuf( std::cout.rdbuf() );
    }
    m_stream << timestamp() << ' ';
    m_stream << severity( m_severity ) << ' ';
    if ( _location.file_name() != "unsupported" ) {

#ifdef _WIN32
      constexpr char delimiter = '\\';
#else
      constexpr char delimiter = '/';
#endif
      std::string filename { _location.file_name() };
      if ( m_locationPath == Path::Filename && filename.find_last_of( delimiter ) != std::string::npos ) {

        const std::size_t pos = filename.find_last_of( delimiter );
        filename = filename.substr( pos + 1, filename.size() - ( pos + 1 ) );
      }
      m_stream << filename << ':' << _location.line() << ' ' << _location.function_name() << ' ';
    }
  }

  Logger::~Logger() noexcept {

    m_stream << '\n';
    m_stream.flush();
  }

  void Logger::printChar( std::int8_t _input ) noexcept {

    m_autoQuotes ? m_stream << "'" << _input << "'" : m_stream << _input;
  }

  void Logger::printString( std::string_view _input ) {

    m_autoQuotes ? m_stream << std::quoted( _input ) : m_stream << _input;
  }

  Logger &Logger::operator<<( std::time_t _input ) noexcept {

    struct std::tm currentLocalTime {};

#ifdef _WIN32
    localtime_s( &currentLocalTime, &_input );
#else
    localtime_r( &_input, &currentLocalTime );
#endif

    m_stream << std::put_time( &currentLocalTime, "%c %Z" );
    return maybeSpace();
  }

  std::string Logger::timestamp() const noexcept {

    return timestamp::iso8601( Precision::MicroSeconds );
  }

  std::string Logger::severity( Severity _severity ) const {

    std::string result {};
    std::string severity( magic_enum::enum_name( _severity ) );
    string_utils::toUpper( severity );
    switch ( _severity ) {

      case Severity::Verbose:
        result += "\x1b[37;1m[" + severity + "]\x1b[0m";
        break;
      case Severity::Debug:
        result += "  \x1b[34;1m[" + severity + "]\x1b[0m";
        break;
      case Severity::Info:
        result += "   \x1b[32;1m[" + severity + "]\x1b[0m";
        break;
      case Severity::Warning:
        result += "\x1b[33;1m[" + severity + "]\x1b[0m";
        break;
      case Severity::Error:
        result += "  \x1b[31;1m[" + severity + "]\x1b[0m";
        break;
      case Severity::Fatal:
        result += "  \x1b[41;1m[" + severity + "]\x1b[0m";
        break;
    }
    return result;
  }
}
