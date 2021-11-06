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

/* stl header */
#include <array>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief The CPU class to receive information about the CPU.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class CPU {

  public:
    /**
     * @brief Default constructor for CPUID.
     * @param _leaf   Leaf register.
     * @param _subleaf   Subleaf of register.
     */
    explicit CPU( unsigned int _leaf = 1,
                  unsigned int _subleaf = 0 );

    /**
     * @brief Return stepping of CPU.
     * @return Stepping of CPU.
     */
    [[nodiscard]] inline unsigned int stepping() const { return m_leaf[0] & 0xF; }

    /**
     * @brief Return model of CPU.
     * @return Model of CPU.
     */
    [[nodiscard]] inline unsigned int model() const { return ( m_leaf[0] >> 4 ) & 0xF; }

    /**
     * @brief Return family of CPU.
     * @return Family of CPU.
     */
    [[nodiscard]] inline unsigned int family() const { return ( m_leaf[0] >> 8 ) & 0xF; }

    /**
     * @brief Return type of CPU.
     * @return Type of CPU.
     */
    [[nodiscard]] inline unsigned int type() const { return ( m_leaf[0] >> 12 ) & 0x3; }

    /**
     * @brief Return extended model of CPU.
     * @return Extended model of CPU.
     */
    [[nodiscard]] inline unsigned int extendedModel() const { return ( m_leaf[0] >> 16 ) & 0xF; }

    /**
     * @brief Return extended family of CPU.
     * @return Extended family of CPU.
     */
    [[nodiscard]] inline unsigned int extendedFamily() const { return ( m_leaf[0] >> 20 ) & 0xFF; }

    /**
     * @brief Does CPU support SMX?
     * @return True, if the CPU supports SMX - otherwise false.
     */
    [[nodiscard]] inline bool smxSupport() const { return ( m_leaf[2] >> 6 ) & 1; }

    /**
     * @brief Does CPU support SGX?
     * @return True, if the CPU supports SGX - otherwise false.
     */
    [[nodiscard]] inline bool sgxSupport() const { return ( m_extendedLeaf[1] >> 2 ) & 0x1; }

    /**
     * @brief Does CPU support SGX launch control?
     * @return True, if the CPU supports SGX launch control - otherwise false.
     */
    [[nodiscard]] inline bool sgxLaunchControlSupport() const { return ( m_extendedLeaf[2] >> 30 ) & 0x01; }

    /**
     * @brief Does CPU support SGX version 1?
     * @return True, if the CPU supports SGX version 1 - otherwise false.
     */
    [[nodiscard]] inline bool sgxVersion1Support() const { return m_sgxLeaf[0] & 0x1; }

    /**
     * @brief Does CPU support SGX version 2?
     * @return True, if the CPU supports SGX version 2 - otherwise false.
     */
    [[nodiscard]] inline bool sgxVersion2Support() const { return ( m_sgxLeaf[0] >> 1 ) & 0x1; }

    /**
     * @brief Returns maximum size of enclave.
     * @return Maximum enclave size.
     */
    [[nodiscard]] inline unsigned int maximumEnclaveSize() const { return m_sgxLeaf[2] & 0xFF; }

    /**
     * @brief Returns maximum size of enclave.
     * @return Maximum enclave size.
     */
    [[nodiscard]] inline unsigned int maximumEnclaveSize64() const { return ( m_sgxLeaf[2] >> 8 ) & 0xFF; }

    /**
     * @brief Return EAX id.
     * @return The EAX id.
     */
    [[nodiscard]] inline unsigned int eax() const { return m_currentLeaf[0]; }

    /**
     * @brief Return EBX id.
     * @return The EBX id.
     */
    [[nodiscard]] inline unsigned int ebx() const { return m_currentLeaf[1]; }

    /**
     * @brief Return ECX id.
     * @return The ECX id.
     */
    [[nodiscard]] inline unsigned int ecx() const { return m_currentLeaf[2]; }

    /**
     * @brief Return EDX id.
     * @return The EDX id.
     */
    [[nodiscard]] inline unsigned int edx() const { return m_currentLeaf[3]; }

    /**
     * @brief Request a special register.
     * @param _leaf   Leaf register.
     * @param _subleaf   Subleaf of register.
     */
    void updateNativeId( unsigned int _leaf = 1,
                         unsigned int _subleaf = 0 );

  private:
    /**
     * @brief Currently asked leaf.
     */
    std::array<unsigned int, 4> m_currentLeaf {};

    /**
     * @brief Information leaf - #1.
     */
    std::array<unsigned int, 4> m_leaf {};

    /**
     * @brief Extended information leaf - #7.
     */
    std::array<unsigned int, 4> m_extendedLeaf {};

    /**
     * @brief SGX information leaf -#12.
     */
    std::array<unsigned int, 4> m_sgxLeaf {};
  };
}
