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

#pragma once

/* c header */
#include <ctime>

/* stl header */
#include <chrono>
#include <string>

/**
 * @brief vx (VX Apps) namespace.
 */
namespace vx {

  /**
   * @brief Print CPU and System Time on called block.
   * @author Florian Becker <fb\@vxapps.com> (VX Apps)
   */
  class Timing {

  public:
    /**
     * @brief Default constructor for Timing.
     */
    Timing() = default;

    /**
     * @brief Start the internal timer or reset.
     */
    void start();

    /**
     * @brief Stop the internal timer and output to stdout.
     */
    void stop() const;

    /**
     * @brief The name of timed action for the output display.
     * @param _action   The name of the action.
     */
    inline void setAction( const std::string &_action ) { m_action = _action; }

    /**
     * @brief The name of timed action for the output display.
     * @return The name of the action.
     */
    inline std::string action() const { return m_action; }

  private:
    /**
     * @brief Name for the current action.
     */
    std::string m_action = {};

    /**
     * @brief Clock to calculate the elapsed system time.
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start = {};

    /**
     * @brief Clock to calculate the elapsed CPU time.
     */
    std::clock_t m_cpu = 0;
  };
}
