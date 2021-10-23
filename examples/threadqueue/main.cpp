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
#include <iostream>

/* modern.cpp.core header */
#include <SharedQueue.h>
#include <Timer.h>

/* local header */
#include "Item.h"

constexpr int intervallSeconds = 1;
constexpr int secondsToMilliseconds = 100;
constexpr int exitIntervall = 30;

static void process( vx::SharedQueue<std::unique_ptr<Item>> &_queue, int _threadId ) {

  std::cout << "Start Thread: " << _threadId << std::endl;
  while ( true ) {

    std::unique_ptr<Item> item = std::move( _queue.front() );
    _queue.pop();
    if ( item ) {

      if ( item->getMessage() == "STOP" ) {

        break;
      }
      std::cout << _threadId << ": received item: " << item->getMessage() << " " << item->getNumber() << std::endl;
    }
  }
  std::cout << "Ended Thread: " << _threadId << std::endl;
}

int main() {

  int intervall {};
  bool stop = false;

  vx::SharedQueue<std::unique_ptr<Item>> queue {};

  unsigned int threadCount = std::max<unsigned int>( 1, std::thread::hardware_concurrency() );
  std::vector<std::thread> threads {};
  threads.reserve( threadCount );

  for ( unsigned int i = 0; i < threadCount; ++i ) {

    threads.emplace_back( std::thread( process, std::ref( queue ), i ) );
  }

  auto intervallTimer = vx::Timer();
  intervallTimer.setInterval( [&intervall, &stop, &queue]() {

    ++intervall;
    std::cout << "Intervall: " << intervall << std::endl;
    queue.push( std::make_unique<Item>( "Attached", intervall ) );
    if ( intervall >= exitIntervall ) {

      stop = true;
    }
  }, intervallSeconds * secondsToMilliseconds );

  while ( true ) {

    /* Leave the app run infinity */
    if ( stop ) {

      break;
    }
  }

  /* Send STOP to finish all threads */
  for ( unsigned int x = 0; x < threads.size() * 2; ++x ) {

    queue.push( std::make_unique<Item>( "STOP", 0 ) );
  }

  /* Wait for threads to be finished */
  for ( auto &thread : threads ) {

    thread.join();
  }
  threads.clear();

  return EXIT_SUCCESS;
}
