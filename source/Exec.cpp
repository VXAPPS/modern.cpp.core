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
#include <array>
#include <iostream>
#include <memory>
#include <sstream>

/* local header */
#include "Exec.h"

namespace vx::exec {

  static int m_resultCode = 0; // NOSONAR const is not possible here.

  /** Buffer size to read stdout. */
  constexpr int bufferSize = 128;

  void close( std::FILE *_file ) noexcept {

#ifdef _MSC_VER
    m_resultCode = _pclose( _file );
#else
    m_resultCode = pclose( _file );
#endif
#ifndef _MSC_VER
    if ( WIFEXITED( m_resultCode ) ) {

      m_resultCode = WEXITSTATUS( m_resultCode );
    }
#endif
  }

  std::string run( const std::string &_command ) noexcept {

    std::array<char, bufferSize> buffer {};
    std::string result {};
#ifdef _MSC_VER
    const std::unique_ptr<FILE, decltype( &close )> pipe( _popen( _command.c_str(), "r" ), &close );
#else
    const std::unique_ptr<std::FILE, decltype( &close )> pipe( popen( _command.c_str(), "r" ), &close );
#endif
    if ( !pipe ) {

      std::cout << "popen() failed for " << _command << std::endl;
      return {};
    }
    while ( std::fgets( buffer.data(), static_cast<int>( buffer.size() ), pipe.get() ) != nullptr ) {

      result += buffer.data();
    }
    return result;
  }

  int resultCode() noexcept { return m_resultCode; }
}
