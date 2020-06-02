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
#include <cstdio>
#include <cstring> // strerror

/* system header */
#include <fcntl.h> // open
#include <termios.h>
#include <unistd.h> // write, read, close

/* stl header */
#include <chrono>
#include <iostream>
#include <vector>

/* local haeder */
#include "Serial.h"

namespace VX {

  /** Flush duration in milliseconds */
  constexpr int flushDurationMs = 150;

  /** Buffer size to read std out */
  constexpr int bufferSize = 1024;

  Serial::Serial( const std::string &_path, Baudrate _baudrate ) {

    /* Open port, checking for errors */
    m_descriptor = ::open( _path.c_str(), ( O_RDWR | O_NOCTTY | O_NDELAY ) );
    if ( m_descriptor == -1 ) {

      std::cout << "Unable to open serial port: " << _path << " at baud rate: " << static_cast<int>( _baudrate ) << std::endl;
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
    options.c_iflag &= static_cast<unsigned long>( ~( INLCR | ICRNL ) );
    options.c_iflag |= IGNPAR | IGNBRK;
    options.c_oflag &= static_cast<unsigned long>( ~( OPOST | ONLCR | OCRNL ) );
    options.c_cflag &= static_cast<unsigned long>( ~( PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS ) );
    options.c_cflag |= CLOCAL | CREAD | CS8;
    options.c_lflag &= static_cast<unsigned long>( ~( ICANON | ISIG | ECHO ) );
    options.c_cc[VTIME] = 1;
    options.c_cc[VMIN]  = 0;

    /* Apply settings */
    /* TCSANOW vs TCSAFLUSH? Was using TCSAFLUSH; settings source above uses TCSANOW. */
    if ( tcsetattr( m_descriptor, TCSANOW, &options ) < 0 ) {

#ifdef DEBUG
      std::cout << "Error setting serial port attributes." << std::endl;
#endif
      close();
      return;
    }
    m_isOpen = true;
  }

  Serial::~Serial() {

    if ( m_isOpen ) {

      close();
    }
  }

  static std::chrono::milliseconds getSteadyClockTimestampMs() {

    return std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now().time_since_epoch() );
  }

  bool Serial::flush() const {

    std::chrono::milliseconds startTimestampMs = getSteadyClockTimestampMs();
    while ( getSteadyClockTimestampMs().count() - startTimestampMs.count() < flushDurationMs ) {

      std::string result = read();
      if ( result.empty() ) {

#ifdef DEBUG
        std::cout << "readSerialData() failed. Error: " << std::strerror( errno ) << std::endl;
#endif
        return false;
      }
    }
    return true;
  }

  bool Serial::write( const std::string &_data ) const {

    ssize_t numBytesWritten = ::write( m_descriptor, _data.c_str(), _data.size() );
    if ( numBytesWritten < 0 ) {

#ifdef DEBUG
      std::cout << "Serial port write() failed. Error: " << std::strerror( errno ) << std::endl;
#endif
      return false;
    }
    return true;
  }

  std::string Serial::read() const {

    std::vector<char> buffer( bufferSize );
    ssize_t numBytesRead = ::read( m_descriptor, buffer.data(), buffer.size() );
    if ( numBytesRead < 0 ) {

#ifdef DEBUG
      std::cout << "Serial port read() failed. Error: " << std::strerror( errno ) << std::endl;
#endif
      return {};
    }
    return std::string( buffer.begin(), buffer.end() );
  }

  void Serial::close() {

    if ( m_isOpen ) {

      ::close( m_descriptor );
      m_descriptor = -1;
    }
  }
}
