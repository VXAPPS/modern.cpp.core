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
#include <cstdint> // std::uint32_t

/* stl header */
#include <chrono>
#include <mutex>
#include <shared_mutex>
#ifdef HAVE_JTHREAD
  #include <thread>
#else
  #include <jthread.hpp>
#endif

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Timing class for timeouts.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class Timer {

  public:
    /**
     * @brief Call a function after timeout.
     * @tparam Function   Function definition.
     * @param _delay   Delay in milliseconds after the function is called.
     * @param _function   Call back function.
     */
    template <typename Function>
    void setTimeout( std::uint32_t _delay,
                     Function _function ) noexcept {

      m_clear = false;
      std::jthread thread( [ &_clear = m_clear, _delay, _function ]() {
        if ( _clear ) {

          return;
        }
        std::this_thread::sleep_for( std::chrono::milliseconds( _delay ) );
        if ( _clear ) {

          return;
        }
        _function();
      } );
      thread.detach();
    }

    /**
     * @brief Call a function after interval.
     * @tparam Function   Function definition.
     * @param _interval   Interval in milliseconds after the function is called.
     * @param _function   Call back function.
     */
    template <typename Function>
    void setInterval( std::uint32_t _interval,
                      Function _function ) noexcept {

      m_clear = false;
      std::jthread thread( [ &_clear = m_clear, _interval, _function ]() {
        while ( true ) {

          if ( _clear ) {

            return;
          }
          std::this_thread::sleep_for( std::chrono::milliseconds( _interval ) );
          if ( _clear ) {

            return;
          }
          _function();
        }
      } );
      thread.detach();
    }

    /**
     * @brief Stopping the current timer not to execute the call back function.
     */
    inline void stop() noexcept {

      const std::unique_lock<std::shared_mutex> lock( m_mutex ); // NOSONAR template argument deduction
      m_clear = true;
    }

    /**
     * @brief Is the timer running?
     * @return True, if the timer is running - otherwise false.
     */
    [[nodiscard]] inline bool isRunning() const noexcept {

      const std::shared_lock<std::shared_mutex> lock( m_mutex ); // NOSONAR template argument deduction
      return !m_clear;
    }

  private:
    /**
     * @brief Clear the timer.
     */
    bool m_clear = false;

    /**
     * @brief Member for shared mutex.
     */
    mutable std::shared_mutex m_mutex {};
  };
}
