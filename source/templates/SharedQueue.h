/*
 * Copyright (c) 2011 Florian Becker <fb@vxapps.com> (VX APPS).
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

/* stl header */
#include <condition_variable>
#include <mutex>
#include <queue>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Template for shared queue class.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   * @tparam T   Type.
   */
  template <typename T>
  class SharedQueue {

  public:
    /**
     * @brief Default constructor for SharedQueue.
     */
    SharedQueue() = default;

    /**
     * @brief Default destructor for SharedQueue.
     */
    ~SharedQueue() = default;

    /**
     * @brief Delete copy assign.
     */
    SharedQueue( const SharedQueue & ) = delete;

    /**
     * @brief Constructor move assign for SharedQueue.
     * @param _other   Other shared queue.
     */
    SharedQueue( SharedQueue &&_other ) noexcept {

      std::scoped_lock<std::mutex> lock( m_mutex );
      m_queue = std::move( _other.m_queue );
    }

    /**
     * @brief Delete copy assign.
     * @return Nothing.
     */
    SharedQueue &operator=( const SharedQueue & ) = delete;

    /**
     * @brief Delete move assign.
     * @return Nothing.
     */
    SharedQueue &operator=( SharedQueue && ) = delete;

    /**
     * @brief Return the item in front.
     * @return The item in front.
     */
    T &front() noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      m_condition.wait( lock, [ this ] { return !m_queue.empty(); } );

      return m_queue.front();
    }

    /**
     * @brief Clean from front item.
     */
    void pop() noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      m_condition.wait( lock, [ this ] { return !m_queue.empty(); } );
      m_queue.pop();
    }

    /**
     * @brief Push an item to the queue.
     * @param item   Item to add.
     */
    void push( const T &item ) noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      m_queue.push( item );

      /* unlock before notificiation to minimize mutex context */
      lock.unlock();

      /* notify one waiting thread */
      m_condition.notify_one();
    }

    /**
     * @brief Push an item to the queue.
     * @param item   Item to add.
     */
    void push( T &&item ) noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      m_queue.push( std::move( item ) );

      /* unlock before notificiation to minimize mutex context */
      lock.unlock();

      /* notify one waiting thread */
      m_condition.notify_one();
    }

    /**
     * @brief Return the size queue size.
     * @return The queue size.
     */
    std::size_t size() const noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      std::size_t size = m_queue.size();

      lock.unlock();
      return size;
    }

    /**
     * @brief Check if the queue is empty.
     * @return True, it the queue is empty - otherwise false.
     */
    bool empty() const noexcept {

      std::unique_lock<std::mutex> lock( m_mutex );

      bool empty = m_queue.empty();

      lock.unlock();
      return empty;
    }

  private:
    /**
     * @brief Member the queue.
     */
    std::queue<T> m_queue {};

    /**
     * @brief Member for shared mutex.
     */
    mutable std::mutex m_mutex {};

    /**
     * @brief Condition member.
     */
    std::condition_variable m_condition {};
  };
}
