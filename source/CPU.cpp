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

#ifdef _WIN32
  #include <intrin.h>
#endif

/* local header */
#include "CPU.h"

namespace vx {

  /** Leaf of extended information. */
  constexpr unsigned int extendedLeaf = 7;

  /** Leaf of SGX information. */
  constexpr unsigned int sgxLeaf = 12;

  CPU::CPU( unsigned int _leaf,
            unsigned int _subleaf ) {

    updateNativeId( sgxLeaf, 0 );
    m_sgxLeaf = m_currentLeaf;
    updateNativeId( extendedLeaf, 0 );
    m_extendedLeaf = m_currentLeaf;
    updateNativeId( 1, 0 );
    m_leaf = m_currentLeaf;
    updateNativeId( _leaf, _subleaf );
  }

  void CPU::updateNativeId( unsigned int _leaf,
                            unsigned int _subleaf ) {

#ifdef _WIN32
    std::array<int, 4> currentLeaf;
    __cpuidex( currentLeaf.data(), _leaf, _subleaf );
    m_currentLeaf[0] = currentLeaf[0];
    m_currentLeaf[1] = currentLeaf[1];
    m_currentLeaf[2] = currentLeaf[2];
    m_currentLeaf[3] = currentLeaf[3];
#else
#ifdef __aarch64__
    /* Not available */
    [[maybe_unused]] _leaf;
    [[maybe_unused]] _subleaf;
#else
    asm volatile
    ( "cpuid" : "=a"( m_currentLeaf[0] ), "=b"( m_currentLeaf[1] ), "=c"( m_currentLeaf[2] ), "=d"( m_currentLeaf[3] )
      : "a"( _leaf ), "c"( _subleaf ) );
#endif
#endif
  }
}
