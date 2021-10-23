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
   */
  template <class T>
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

    T &front() noexcept;
    void pop() noexcept;

    void push( const T &item ) noexcept;
    void push( T &&item ) noexcept;

    std::size_t size() noexcept;
    bool empty() noexcept;

  private:
    std::queue<T> m_queue {};
    mutable std::mutex m_mutex {};
    std::condition_variable m_condition {};
  };

  template <typename T>
  T &SharedQueue<T>::front() noexcept {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_condition.wait( lock, [this]{ return !m_queue.empty(); } );
    return m_queue.front();
  }

  template <typename T>
  void SharedQueue<T>::pop() noexcept {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_condition.wait( lock, [this]{ return !m_queue.empty(); } );
    m_queue.pop();
  }

  template <typename T>
  void SharedQueue<T>::push( const T &item ) noexcept {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_queue.push( item );
    lock.unlock();     // unlock before notificiation to minimize mutex context
    m_condition.notify_one(); // notify one waiting thread
  }

  template <typename T>
  void SharedQueue<T>::push( T &&item ) noexcept {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_queue.push( std::move( item ) );
    lock.unlock();     // unlock before notificiation to minimize mutex context
    m_condition.notify_one(); // notify one waiting thread
  }

  template <typename T>
  std::size_t SharedQueue<T>::size() noexcept {

    std::unique_lock<std::mutex> lock( m_mutex );
    std::size_t size = m_queue.size();
    lock.unlock();
    return size;
  }
}
