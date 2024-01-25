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
#include <ctime>

/* stl header */
#include <chrono>
#include <exception>
#include <iomanip>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string>
#include <utility>

/* local header */
#include "Cpp23.h"
#include "Logger.h"
#include "Timestamp.h"

namespace vx::timestamp {

  /* get a precise timestamp as a string */
  std::string iso8601( Precision _precision ) {

    struct std::tm currentLocalTime {};

    const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    const std::time_t nowAsTimeT = std::chrono::system_clock::to_time_t( now );

#ifdef _WIN32
    localtime_s( &currentLocalTime, &nowAsTimeT );
#else
    localtime_r( &nowAsTimeT, &currentLocalTime );
#endif

    std::stringstream nowSs {};
    nowSs << std::put_time( &currentLocalTime, "%Y-%m-%dT%T" );
    switch ( _precision ) {

      case Precision::Seconds:
        break;
      case Precision::MilliSeconds: {

        const auto nowMilli = std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ) % std::milli::den;
        nowSs << '.' << std::setfill( '0' ) << std::setw( std::to_underlying( _precision ) );
        nowSs << nowMilli.count();
        break;
      }
      case Precision::MicroSeconds: {

        const auto nowMicro = std::chrono::duration_cast<std::chrono::microseconds>( now.time_since_epoch() ) % std::micro::den;
        nowSs << '.' << std::setfill( '0' ) << std::setw( std::to_underlying( _precision ) );
        nowSs << nowMicro.count();
        break;
      }
      case Precision::NanoSeconds: {

        const auto nowNano = std::chrono::duration_cast<std::chrono::nanoseconds>( now.time_since_epoch() ) % std::nano::den;
        nowSs << '.' << std::setfill( '0' ) << std::setw( std::to_underlying( _precision ) );
        nowSs << nowNano.count();
        break;
      }
    }

    std::stringstream offset {};
    offset << std::put_time( &currentLocalTime, "%z" );
    if ( offset.peek() != decltype( offset )::traits_type::eof() ) {

      offset.seekp( -2, std::ios_base::end );
      offset << ':';
      offset.seekp( 0, std::ios_base::end );
      offset << '0';
    }

    std::string result {};
    try {

      nowSs << offset.str();
      result = nowSs.str();
    }
    catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

      logFatal() << _exception.what();
    }
    return result;
  }
}
