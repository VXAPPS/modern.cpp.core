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
#include <iomanip>
#include <iostream>

/* local header */
#include "Timing.h"

namespace VX {

  /** Multiplier from nanoseconds to milliseconds to seconds and vice versa. */
  constexpr double multiplier = 1000.0;

  void Timing::start() {

    m_start = std::chrono::high_resolution_clock::now();
    m_cpu = std::clock();
  }

  void Timing::stop() {

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "------ " << m_action << std::endl;
    std::cout << "Real Time: " << std::setprecision( std::numeric_limits<double>::digits10 + 1 ) << std::chrono::duration_cast<std::chrono::nanoseconds>( end - m_start ).count() / multiplier / multiplier << " ms" << std::endl;
    std::cout << "CPU Time: " << std::setprecision( std::numeric_limits<double>::digits10 + 1 ) << multiplier * static_cast<double>( std::clock() - m_cpu ) / CLOCKS_PER_SEC << " ms" << std::endl;
  }
}