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
#include <optional>

/* magic_enum */
#include <magic_enum.hpp>

/* local header */
#include "Logger.h"

/**
 * @brief vx (VX APPS) logger namespace.
 */
namespace vx::logger {

  /**
   * @brief Logger operator for enumeration.
   * @param _logger   Logger as input.
   * @param _value   Enumeration to logger.
   * @return Logger with output.
   */
  template <typename E, magic_enum::detail::enable_if_t<E, int> = 0>
  inline Logger &operator<<( Logger &_logger,
                             E _value ) noexcept {

    using D = std::decay_t<E>;
    using U = magic_enum::underlying_type_t<D>;

    if constexpr ( magic_enum::detail::supported<D>::value ) {

      if ( const auto name = magic_enum::enum_name<D, magic_enum::as_flags<magic_enum::detail::is_flags_v<D>>>( _value ); !name.empty() ) {

        _logger.stream() << name;
        return _logger.maybeSpace();
      }
    }
    _logger.stream() << static_cast<U>( _value );
    return _logger.maybeSpace();
  }

  /**
   * @brief Logger operator for enumeration optional.
   * @param _logger   Logger as input.
   * @param _value   Enumeration to logger.
   * @return Logger with output.
   */
  template <typename E, magic_enum::detail::enable_if_t<E, int> = 0>
  inline Logger &operator<<( Logger &_logger,
                             magic_enum::optional<E> _value ) noexcept {

    _value ? _logger << *_value : _logger.stream() << "(nullopt)";
    return _logger.maybeSpace();
  }
}
