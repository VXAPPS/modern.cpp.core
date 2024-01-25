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
#include <cerrno>
#include <cstddef> // std::size_t
#include <cstdint> // std::int32_t
#include <cstdio>
#include <cstring> // strerror_r

/* system header */
#include <sys/fcntl.h> // open
#include <termios.h>
#include <unistd.h> // write, read, close

/* stl header */
#include <chrono>
#include <exception>
#include <new> // std::bad_alloc
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/* local header */
#include "Cpp23.h"
#include "Logger.h"
#include "Serial.h"

namespace vx {

  /** @brief Flush duration in milliseconds. */
  constexpr std::int32_t flushDurationMs = 150;

  /** @brief Buffer size to read std out. */
  constexpr std::int32_t bufferSize = 1024;

  /** @brief Buffer size for errno. */
  constexpr std::int32_t errnoBufferSize = 128;

  Serial::Serial( const std::string &_path,
                  Baudrate _baudrate ) noexcept
    : m_descriptor( ::open( _path.c_str(), ( O_RDWR | O_NOCTTY | O_NONBLOCK ) ) ) {

    /* Open port, checking for errors */
    if ( m_descriptor == -1 ) {

      logFatal() << "Unable to open serial port:" << _path << "at baud rate:" << std::to_underlying( _baudrate );
      return;
    }

    /* Configure i/o baud rate settings */
    struct termios options = {};
    tcgetattr( m_descriptor, &options );
    switch ( _baudrate ) {

      case Baudrate::Speed9600:
        cfsetispeed( &options, B9600 );
        cfsetospeed( &options, B9600 );
        break;
      case Baudrate::Speed19200:
        cfsetispeed( &options, B19200 );
        cfsetospeed( &options, B19200 );
        break;
      case Baudrate::Speed38400:
        cfsetispeed( &options, B38400 );
        cfsetospeed( &options, B38400 );
        break;
      case Baudrate::Speed57600:
        cfsetispeed( &options, B57600 );
        cfsetospeed( &options, B57600 );
        break;
    }

    /* Configure other settings */
    /* Settings from: */
    /* https://github.com/Marzac/rs232/blob/master/rs232-linux.c */
    options.c_iflag &= static_cast<std::uint64_t>( ~( INLCR | ICRNL ) );
    options.c_iflag |= IGNPAR | IGNBRK;
    options.c_oflag &= static_cast<std::uint64_t>( ~( OPOST | ONLCR | OCRNL ) );
    options.c_cflag &= static_cast<std::uint64_t>( ~( PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS ) );
    options.c_cflag |= CLOCAL | CREAD | CS8;
    options.c_lflag &= static_cast<std::uint64_t>( ~( ICANON | ISIG | ECHO ) );
    options.c_cc[ VTIME ] = 1;
    options.c_cc[ VMIN ] = 0;

    /* Apply settings */
    /* TCSANOW vs TCSAFLUSH? Was using TCSAFLUSH; settings source above uses TCSANOW. */
    if ( tcsetattr( m_descriptor, TCSANOW, &options ) < 0 ) {

      logFatal() << "Error setting serial port attributes.";
      close();
      return;
    }
    m_isOpen = true;
  }

  Serial::~Serial() noexcept {

    if ( m_isOpen ) {

      close();
    }
  }

  namespace {

    /**
     * @brief Return timestamp in milliseconds.
     * @return Timestamp in milliseconds.
     */
    inline std::chrono::milliseconds timestampMs() noexcept {

      return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now().time_since_epoch() );
    }
  }

  bool Serial::flush() const {

    const std::chrono::milliseconds startTimestampMs = timestampMs();
    while ( timestampMs().count() - startTimestampMs.count() < flushDurationMs ) {

      const std::string result = read();
      if ( result.empty() ) {

        std::vector<char> errnoBuffer {};
        try {

          errnoBuffer.resize( errnoBufferSize );
        }
        catch ( const std::bad_alloc &_exception ) {

          logFatal() << "bad_alloc:" << _exception.what();
        }
        catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

          logFatal() << _exception.what();
        }
        std::ignore = strerror_r( errno, errnoBuffer.data(), errnoBuffer.size() );
        logError() << "Serial port read() failed. Error:" << std::string( std::cbegin( errnoBuffer ), std::cend( errnoBuffer ) );
        return false;
      }
    }
    return true;
  }

  bool Serial::write( const std::string &_data ) const noexcept {

    if ( ::write( m_descriptor, _data.c_str(), _data.size() ) < 0 ) {

      std::vector<char> errnoBuffer {};
      try {

        errnoBuffer.resize( errnoBufferSize );
      }
      catch ( const std::bad_alloc &_exception ) {

        logFatal() << "bad_alloc:" << _exception.what();
      }
      catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

        logFatal() << _exception.what();
      }
      std::ignore = strerror_r( errno, errnoBuffer.data(), errnoBuffer.size() );
      logError() << "Serial port write() failed. Error:" << std::string( std::cbegin( errnoBuffer ), std::cend( errnoBuffer ) );
      return false;
    }
    return true;
  }

  std::string Serial::read() const {

    std::vector<char> buffer {};
    ssize_t numBytesRead {};
    try {

      buffer.resize( bufferSize );
      numBytesRead = ::read( m_descriptor, buffer.data(), buffer.size() );
      buffer.resize( static_cast<std::size_t>( numBytesRead ) );
    }
    catch ( const std::bad_alloc &_exception ) {

      logFatal() << "bad_alloc:" << _exception.what();
    }
    catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

      logFatal() << _exception.what();
    }
    if ( numBytesRead < 0 ) {

      std::vector<char> errnoBuffer {};
      try {

        errnoBuffer.resize( errnoBufferSize );
      }
      catch ( const std::bad_alloc &_exception ) {

        logFatal() << "bad_alloc:" << _exception.what();
      }
      catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

        logFatal() << _exception.what();
      }
      std::ignore = strerror_r( errno, errnoBuffer.data(), errnoBuffer.size() );
      logError() << "Serial port read() failed. Error:" << std::string( std::cbegin( errnoBuffer ), std::cend( errnoBuffer ) );
      return {};
    }
    return { std::cbegin( buffer ), std::cend( buffer ) };
  }

  void Serial::close() noexcept {

    if ( m_isOpen ) {

      ::close( m_descriptor );
      m_descriptor = -1;
    }
  }
}
