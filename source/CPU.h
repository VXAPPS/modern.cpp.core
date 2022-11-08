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
#include <array>

/* magic enum */
#include <magic_enum.hpp>

/* local header */
#include "Cpp23.h"

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
     * @brief The cpu register enum
     */
    enum class Register {

      EAX, /**< EAX register. */
      EBX, /**< EBX register. */
      ECX, /**< ECX register. */
      EDX  /**< EDX register. */
    };

    /**
     * @brief Default constructor for CPUID.
     * @param _leaf   Leaf register.
     * @param _subleaf   Subleaf of register.
     */
    explicit CPU( std::uint32_t _leaf = 1,
                  std::uint32_t _subleaf = 0 ) noexcept;

    /**
     * @brief Return stepping of CPU.
     * @return Stepping of CPU.
     */
    [[nodiscard]] inline std::uint32_t stepping() const noexcept { return m_leaf[ std::to_underlying( Register::EAX ) ] & 15U; }

    /**
     * @brief Return model of CPU.
     * @return Model of CPU.
     */
    [[nodiscard]] inline std::uint32_t model() const noexcept { return ( m_leaf[ std::to_underlying( Register::EAX ) ] >> 4U ) & 15U; }

    /**
     * @brief Return family of CPU.
     * @return Family of CPU.
     */
    [[nodiscard]] inline std::uint32_t family() const noexcept { return ( m_leaf[ std::to_underlying( Register::EAX ) ] >> 8U ) & 15U; }

    /**
     * @brief Return type of CPU.
     * @return Type of CPU.
     */
    [[nodiscard]] inline std::uint32_t type() const noexcept { return ( m_leaf[ std::to_underlying( Register::EAX ) ] >> 12U ) & 3U; }

    /**
     * @brief Return extended model of CPU.
     * @return Extended model of CPU.
     */
    [[nodiscard]] inline std::uint32_t extendedModel() const noexcept { return ( m_leaf[ std::to_underlying( Register::EAX ) ] >> 16U ) & 15U; }

    /**
     * @brief Return extended family of CPU.
     * @return Extended family of CPU.
     */
    [[nodiscard]] inline std::uint32_t extendedFamily() const noexcept { return ( m_leaf[ std::to_underlying( Register::EAX ) ] >> 20U ) & 255U; }

    /**
     * @brief Does CPU support SMX?
     * @return True, if the CPU supports SMX - otherwise false.
     */
    [[nodiscard]] inline bool smxSupport() const noexcept { return ( m_leaf[ std::to_underlying( Register::ECX ) ] >> 6U ) & 1U; }

    /**
     * @brief Does CPU support SGX?
     * @return True, if the CPU supports SGX - otherwise false.
     */
    [[nodiscard]] inline bool sgxSupport() const noexcept { return ( m_extendedLeaf[ std::to_underlying( Register::EBX ) ] >> 2U ) & 1U; }

    /**
     * @brief Does CPU support SGX launch control?
     * @return True, if the CPU supports SGX launch control - otherwise false.
     */
    [[nodiscard]] inline bool sgxLaunchControlSupport() const noexcept { return ( m_extendedLeaf[ std::to_underlying( Register::ECX ) ] >> 30U ) & 1U; }

    /**
     * @brief Does CPU support SGX version 1?
     * @return True, if the CPU supports SGX version 1 - otherwise false.
     */
    [[nodiscard]] inline bool sgxVersion1Support() const noexcept { return m_sgxLeaf[ std::to_underlying( Register::EAX ) ] & 1U; }

    /**
     * @brief Does CPU support SGX version 2?
     * @return True, if the CPU supports SGX version 2 - otherwise false.
     */
    [[nodiscard]] inline bool sgxVersion2Support() const noexcept { return ( m_sgxLeaf[ std::to_underlying( Register::EAX ) ] >> 1U ) & 1U; }

    /**
     * @brief Returns maximum size of enclave.
     * @return Maximum enclave size.
     */
    [[nodiscard]] inline std::uint32_t maximumEnclaveSize() const noexcept { return m_sgxLeaf[ std::to_underlying( Register::EDX ) ] & 255U; }

    /**
     * @brief Returns maximum size of enclave.
     * @return Maximum enclave size.
     */
    [[nodiscard]] inline std::uint32_t maximumEnclaveSize64() const noexcept { return ( m_sgxLeaf[ std::to_underlying( Register::EDX ) ] >> 8U ) & 255U; }

    /**
     * @brief Return EAX id.
     * @return The EAX id.
     */
    [[nodiscard]] inline std::uint32_t eax() const noexcept { return m_currentLeaf[ std::to_underlying( Register::EAX ) ]; }

    /**
     * @brief Return EBX id.
     * @return The EBX id.
     */
    [[nodiscard]] inline std::uint32_t ebx() const noexcept { return m_currentLeaf[ std::to_underlying( Register::EBX ) ]; }

    /**
     * @brief Return ECX id.
     * @return The ECX id.
     */
    [[nodiscard]] inline std::uint32_t ecx() const noexcept { return m_currentLeaf[ std::to_underlying( Register::ECX ) ]; }

    /**
     * @brief Return EDX id.
     * @return The EDX id.
     */
    [[nodiscard]] inline std::uint32_t edx() const noexcept { return m_currentLeaf[ std::to_underlying( Register::EDX ) ]; }

    /**
     * @brief Request a special register.
     * @param _leaf   Leaf register.
     * @param _subleaf   Subleaf of register.
     */
    void updateNativeId( std::uint32_t _leaf = 1,
                         std::uint32_t _subleaf = 0 ) noexcept;

  private:
    /**
     * @brief Currently asked leaf.
     */
    std::array<unsigned int, magic_enum::enum_count<Register>()> m_currentLeaf {};

    /**
     * @brief Information leaf - #1.
     */
    std::array<unsigned int, magic_enum::enum_count<Register>()> m_leaf {};

    /**
     * @brief Extended information leaf - #7.
     */
    std::array<unsigned int, magic_enum::enum_count<Register>()> m_extendedLeaf {};

    /**
     * @brief SGX information leaf -#12.
     */
    std::array<unsigned int, magic_enum::enum_count<Register>()> m_sgxLeaf {};
  };
}
