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
//#include <mutex>
#include <queue>
#include <shared_mutex>

namespace vx {

  template <class T>
  class SharedQueue {

  public:
    SharedQueue();
    ~SharedQueue();

    T &front();
    void pop_front();

    void push_back( const T &item );
    void push_back( T &&item );

    int size();
    bool empty();

  private:
    std::deque<T> m_queue;
    mutable std::mutex m_mutex;
//    mutable std::shared_mutex m_mutex;
    std::condition_variable m_condition;
  };

  template <typename T>
  SharedQueue<T>::SharedQueue() {}

  template <typename T>
  SharedQueue<T>::~SharedQueue() {}

  template <typename T>
  T &SharedQueue<T>::front() {

    std::unique_lock<std::mutex> lock( m_mutex );
    while ( m_queue.empty() ) {

      m_condition.wait( lock );
    }
    return m_queue.front();
  }

  template <typename T>
  void SharedQueue<T>::pop_front() {

    std::unique_lock<std::mutex> lock( m_mutex );
    while ( m_queue.empty() ) {

      m_condition.wait( lock );
    }
    m_queue.pop_front();
  }

  template <typename T>
  void SharedQueue<T>::push_back( const T &item ) {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_queue.push_back( item );
    lock.unlock();     // unlock before notificiation to minimize mutex context
    m_condition.notify_one(); // notify one waiting thread
  }

  template <typename T>
  void SharedQueue<T>::push_back( T &&item ) {

    std::unique_lock<std::mutex> lock( m_mutex );
    m_queue.push_back( std::move( item ) );
    lock.unlock();     // unlock before notificiation to minimize mutex context
    m_condition.notify_one(); // notify one waiting thread
  }

  template <typename T>
  int SharedQueue<T>::size() {

    std::unique_lock<std::mutex> lock( m_mutex );
    int size = m_queue.size();
    lock.unlock();
    return size;
  }
}
