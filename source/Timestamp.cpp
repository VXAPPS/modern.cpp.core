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

/* stl header */
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

/* local header */
#include "Timestamp.h"

namespace vx {

  std::string timestampIso8601( Precision _precision ) noexcept {

    (void)_precision;

    /* get a precise timestamp as a string */
    struct std::tm currentLocalTime {};

    const auto now = std::chrono::system_clock::now();
    const auto nowAsTimeT = std::chrono::system_clock::to_time_t( now );
    const auto nowMilli = std::chrono::duration_cast<std::chrono::milliseconds>( now.time_since_epoch() ) % 1000;
    const auto nowMicro = std::chrono::duration_cast<std::chrono::microseconds>( now.time_since_epoch() ) % 1000000;
    const auto nowNano = std::chrono::duration_cast<std::chrono::nanoseconds>( now.time_since_epoch() ) % 1000000000;

#ifdef _WIN32
    localtime_s( &currentLocalTime, &nowAsTimeT );
#else
    localtime_r( &nowAsTimeT, &currentLocalTime );
#endif

    std::ostringstream nowSs;
    nowSs << std::put_time( &currentLocalTime, "%Y-%m-%dT%T" );
    if ( _precision != Precision::Seconds ) {

      nowSs << '.' << std::setfill( '0' ) << std::setw( static_cast<int>( _precision ) );
      switch ( _precision ) {

        case Precision::MilliSeconds:
          nowSs << nowMilli.count();
          break;
        case Precision::MicroSeconds:
          nowSs << nowMicro.count();
          break;
        case Precision::NanoSeconds:
          nowSs << nowNano.count();
          break;
        case Precision::Seconds:
          break;
      }
    }
    nowSs << std::put_time( &currentLocalTime, "%z" );

    std::string result = nowSs.str();
    /* somewhat special - maybe see systemtimeformatter */
    result.replace( result.end() - 2, result.end() - 2, ":" );
    return result;
  }
}
