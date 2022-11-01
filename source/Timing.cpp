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

/* windows header */
#ifdef _WIN32_REVIEW
  #include <processthreadsapi.h>
#endif

/* stl header */
#include <iomanip>
#include <sstream>

/* local header */
#include "Logger.h"
#include "Timestamp.h"
#include "Timing.h"

namespace vx {

  using timestamp::Precision;

  /** Multiplier from nanoseconds to milliseconds to seconds and vice versa. */
  constexpr double multiplier = 1000.0;

#ifdef _WIN32_REVIEW
  static double get_cpu_time() {

    FILETIME a, b, c, d;
    if ( GetProcessTimes( GetCurrentProcess(), &a, &b, &c, &d ) != 0 ) {

      //  Returns total user time.
      //  Can be tweaked to include kernel times as well.
      return (double)( d.dwLowDateTime |
                       ( (unsigned long long)d.dwHighDateTime << 32 ) ) *
             0.0000001;
    }
    else {
      //  Handle error
      return 0;
    }
  }
#endif

  Timing::Timing( std::string_view _action,
                  bool _autoStart ) noexcept {

    if ( _autoStart ) { start( _action ); }
  }

  void Timing::start( std::string_view _action ) noexcept {

    if ( !_action.empty() ) {

      setAction( _action );
    }

    m_start = std::chrono::high_resolution_clock::now();
    m_cpu = std::clock();
  }

  void Timing::stop() const noexcept {

    auto end = std::chrono::high_resolution_clock::now();

    /* Auto scale from ms to s */
    std::string literal = "ms";
    double diff = static_cast<double>( std::chrono::duration_cast<std::chrono::nanoseconds>( end - m_start ).count() ) / multiplier / multiplier;
    if ( diff > multiplier ) {

      literal = "s";
      diff = diff / multiplier;
    }

    std::ostringstream realTime {};
    realTime << std::setprecision( std::numeric_limits<double>::digits10 ) << diff;

    std::ostringstream cpuTime {};
    cpuTime << std::setprecision( std::numeric_limits<double>::digits10 ) << static_cast<double>( std::clock() - m_cpu ) / static_cast<double>( CLOCKS_PER_SEC ) * multiplier;

    logVerbose().stream() << "------ " << m_action;
    logVerbose().stream() << "Timestamp: " << timestamp::iso8601( Precision::MicroSeconds );
    logVerbose().stream() << "Real Time: " << realTime.str() << ' ' << literal;
    logVerbose().stream() << "CPU Time: " << cpuTime.str() << ' ' << "ms";
  }
}
