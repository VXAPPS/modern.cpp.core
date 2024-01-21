/*
 * Copyright (c) 2021 Florian Becker <fb@vxapps.com> (VX APPS).
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
#include <cstdint> // std::int32_t

/* stl header */
#include <algorithm>
#include <iostream>
#include <ranges>

/* modern.cpp.core */
#include <SharedQueue.h>
#include <Timer.h>

/* local header */
#include "Item.h"

constexpr std::int32_t intervalSeconds = 1;
constexpr std::int32_t secondsToMilliseconds = 100;
constexpr std::int32_t exitInterval = 30;

static inline void process( vx::SharedQueue<Item *> &_queue,
                            std::int32_t _threadId ) {

  std::cout << "Start Thread: " << _threadId << std::endl;
  while ( true ) {

    std::unique_ptr<Item> item { _queue.front() };
    if ( item && item->getMessage() == "STOP" ) {

      break;
    }
    if ( item ) {

      std::cout << _threadId << ": received item: " << item->getMessage() << " " << item->getNumber() << std::endl;
    }
  }
  std::cout << "Ended Thread: " << _threadId << std::endl;
}

std::int32_t main() {

  std::int32_t interval {};

  vx::SharedQueue<Item *> queue {};

  const std::uint32_t threadCount = std::max( 1U, std::thread::hardware_concurrency() );
  std::vector<std::jthread> threads {};
  try {

    threads.reserve( threadCount );
  }
  catch ( const std::bad_alloc &_exception ) {

    std::cout << "bad_alloc: " << _exception.what() << std::endl;
  }
  catch ( const std::exception &_exception ) {

    std::cout << _exception.what() << std::endl;
  }

  for ( std::uint32_t i = 0; i < threadCount; ++i ) {

    threads.emplace_back( process, std::ref( queue ), i );
  }

  auto intervalTimer = vx::Timer();

  const auto runOnInterval = [ &intervalTimer, &interval, &queue ]() {
    ++interval;
    std::cout << "Interval: " << interval << std::endl;
    try {

      queue.push( new Item( "Attached", interval ) );
    }
    catch ( const std::bad_alloc &_exception ) {

      std::cout << "bad_alloc: " << _exception.what() << std::endl;
    }
    catch ( const std::exception &_exception ) {

      std::cout << _exception.what() << std::endl;
    }

    if ( interval >= exitInterval ) {

      intervalTimer.stop();
    }
  };

  intervalTimer.setInterval( intervalSeconds * secondsToMilliseconds, runOnInterval );

  while ( true ) {

    /* Leave the app run infinity */
    if ( !intervalTimer.isRunning() ) {

      break;
    }
  }

  const auto stop = [ &queue ]( const std::jthread &_thread ) {
    std::ignore = _thread;
    try {

      queue.push( new Item( "STOP", 0 ) );
    }
    catch ( const std::bad_alloc &_exception ) {

      std::cout << "bad_alloc: " << _exception.what() << std::endl;
    }
    catch ( const std::exception &_exception ) {

      std::cout << _exception.what() << std::endl;
    }
  };

  /* Send STOP to finish all threads */
  std::ranges::for_each( threads, stop );

  /* Wait for threads to be finished */
  for ( auto &thread : threads ) {

    thread.join();
  }
  threads.clear();

  return EXIT_SUCCESS;
}
