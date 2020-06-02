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

#ifdef _WIN32
  #include <climits>
  #include <intrin.h>
  using uint32_t = unsigned __int32;
#else
  #include <stdint.h>
#endif

/**
 * @brief VX (VX Apps) Namespace.
 */
namespace VX {

  /**
   * @brief The CPUID class for receiving CPU id.
   * @author Florian Becker <fb\@vxapps.com> (VX Apps)
   */
  class CPUID {

  public:
    /**
     * @brief Default constructor for CPUID.
     * @param _i   Core id.
     */
    explicit CPUID( int _i ) {

#ifdef _WIN32
      __cpuid( ( int * )regs, _i );

#else
      asm volatile
      ( "cpuid" : "=a"( regs[0] ), "=b"( regs[1] ), "=c"( regs[2] ), "=d"( regs[3] )
        : "a"( _i ), "c"( 0 ) );
      /* ECX is set to zero for CPUID function 4 */
#endif
    }

    /**
     * @brief Return EAX id.
     * @return The EAX id.
     */
    uint32_t EAX() const { return regs[0]; }

    /**
     * @brief Return EBX id.
     * @return The EBX id.
     */
    uint32_t EBX() const { return regs[1]; }

    /**
     * @brief Return ECX id.
     * @return The ECX id.
     */
    uint32_t ECX() const { return regs[2]; }

    /**
     * @brief Return EDX id.
     * @return The EDX id.
     */
    uint32_t EDX() const { return regs[3]; }

  private:
//    std::vector<uint32_t> m_regs;
    /**
     * @brief Reg parts.
     * @todo: Convert to vector<int>.
     */
    uint32_t regs[4] = {};
  };
}
