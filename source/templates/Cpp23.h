/*
 * Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
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
#include <type_traits>

/**
 * @brief std (Standard template library) namespace.
 */
namespace std {

#if !__has_cpp_attribute( __cpp_lib_to_underlying )
  /**
   * @brief Return the underlying value in its correct type of an enumeration.
   * <a href="https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p1682r3.html">https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p1682r3.html</a>
   * @param _enum   Enumeration value.
   * @return The underlying value in its correct type of an enumeration.
   */
  template <typename E>
  constexpr typename std::underlying_type<E>::type to_underlying( E _enum ) noexcept {

    return static_cast<typename std::underlying_type<E>::type>( _enum );
  }
#endif

#if !__has_cpp_attribute( __cpp_lib_unreachable )
  /**
   * @brief Unreachable section is reached.
   */
  [[noreturn]] inline void unreachable() {

    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
  #ifdef __GNUC__ // GCC, Clang, ICC
    __builtin_unreachable();
  #elifdef _MSC_VER // MSVC
    __assume( false );
  #endif
  }
#endif
}
