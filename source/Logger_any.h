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

/* c header */
#include <cstdint> // std::int8_t, std::int32_t

/* stl header */
#include <any>
#include <array>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility> // std::pair
#include <variant>
#include <vector>

/* local header */
#include "Demangle.h"
#include "Logger_container.h"

/**
 * @brief vx (VX APPS) logger namespace.
 */
namespace vx::logger {

  /**
   * @brief Add visitor.
   * @param _function   Visitor function.
   * @return Pair of type and possible visitor.
   */
  template <typename T, typename Function>
  inline std::pair<const std::type_index, std::function<void( Logger &, const std::any & )>> add( const Function &_function ) noexcept {

    return {

      std::type_index( typeid( T ) ),
      [ function = _function ]( Logger &_logger,
                                [[maybe_unused]] const std::any &_any ) {
        function( _logger, std::any_cast<const T &>( _any ) );
      }
    };
  }

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wexit-time-destructors"
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
  /**
   * @brief Map of possible visitors for std::any.
   */
  const std::unordered_map<std::type_index, std::function<void( Logger &_logger, const std::any & )>> visitors {

    add<bool>( []( Logger &_logger, bool _input ) noexcept { _logger << _input; } ),
    add<std::int8_t>( []( Logger &_logger, std::int8_t _input ) noexcept { _logger << _input; } ),
    add<std::int32_t>( []( Logger &_logger, std::int32_t _input ) noexcept { _logger << _input; } ),
    add<std::uint32_t>( []( Logger &_logger, std::uint32_t _input ) noexcept { _logger << _input; } ),
    add<std::size_t>( []( Logger &_logger, std::size_t _input ) noexcept { _logger << _input; } ),
    add<float>( []( Logger &_logger, float _input ) noexcept { _logger << _input; } ),
    add<double>( []( Logger &_logger, double _input ) noexcept { _logger << _input; } ),
    add<const char *>( []( Logger &_logger, const char *_input ) noexcept { _logger << _input; } ),
    add<std::string_view>( []( Logger &_logger, std::string_view _input ) noexcept { _logger << _input; } ),
    add<std::string>( []( Logger &_logger, const std::string &_input ) noexcept { _logger << _input; } ),
    add<std::list<bool>>( []( Logger &_logger, const std::list<bool> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::int8_t>>( []( Logger &_logger, const std::list<std::int8_t> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::int32_t>>( []( Logger &_logger, const std::list<std::int32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::uint32_t>>( []( Logger &_logger, const std::list<std::uint32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::size_t>>( []( Logger &_logger, const std::list<std::size_t> &_input ) noexcept { _logger << _input; } ),
    add<std::list<float>>( []( Logger &_logger, const std::list<float> &_input ) noexcept { _logger << _input; } ),
    add<std::list<double>>( []( Logger &_logger, const std::list<double> &_input ) noexcept { _logger << _input; } ),
    add<std::list<const char *>>( []( Logger &_logger, const std::list<const char *> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::string_view>>( []( Logger &_logger, const std::list<std::string_view> &_input ) noexcept { _logger << _input; } ),
    add<std::list<std::string>>( []( Logger &_logger, const std::list<std::string> &_input ) noexcept { _logger << _input; } ),
    add<std::set<bool>>( []( Logger &_logger, const std::set<bool> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::int8_t>>( []( Logger &_logger, const std::set<std::int8_t> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::int32_t>>( []( Logger &_logger, const std::set<std::int32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::uint32_t>>( []( Logger &_logger, const std::set<std::uint32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::size_t>>( []( Logger &_logger, const std::set<std::size_t> &_input ) noexcept { _logger << _input; } ),
    add<std::set<float>>( []( Logger &_logger, const std::set<float> &_input ) noexcept { _logger << _input; } ),
    add<std::set<double>>( []( Logger &_logger, const std::set<double> &_input ) noexcept { _logger << _input; } ),
    add<std::set<const char *>>( []( Logger &_logger, const std::set<const char *> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::string_view>>( []( Logger &_logger, const std::set<std::string_view> &_input ) noexcept { _logger << _input; } ),
    add<std::set<std::string>>( []( Logger &_logger, const std::set<std::string> &_input ) noexcept { _logger << _input; } ),
    // MAC found that ambiguous...    add<std::vector<bool>>( []( Logger & _logger, const std::vector<bool> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::int8_t>>( []( Logger &_logger, const std::vector<std::int8_t> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::int32_t>>( []( Logger &_logger, const std::vector<std::int32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::uint32_t>>( []( Logger &_logger, const std::vector<std::uint32_t> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::size_t>>( []( Logger &_logger, const std::vector<std::size_t> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<float>>( []( Logger &_logger, const std::vector<float> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<double>>( []( Logger &_logger, const std::vector<double> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<const char *>>( []( Logger &_logger, const std::vector<const char *> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::string_view>>( []( Logger &_logger, const std::vector<std::string_view> &_input ) noexcept { _logger << _input; } ),
    add<std::vector<std::string>>( []( Logger &_logger, const std::vector<std::string> &_input ) noexcept { _logger << _input; } ),
    // VC2017 issue    add<void>( []( Logger & _logger, void *_input ) noexcept { _logger << _input; } ),
  };
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

  /**
   * @brief Visit possible visitors.
   * @param _logger   Logger for a visitor.
   * @param _any   Type of std::any.
   */
  inline void visit( Logger &_logger,
                     const std::any &_any ) {

    if ( const auto iterator = visitors.find( std::type_index( _any.type() ) ); iterator != visitors.cend() ) {

      iterator->second( _logger, _any );
    }
    else {

      _logger.stream() << "unregistered: " << demangle::extreme( _any.type().name() );
    }
  }

  /**
   * @brief Register new visitor.
   * @param _function   Visitor function.
   */
  template <typename T, typename Function>
  inline void registerVisitor( const Function &_function ) noexcept {

    visitors.insert( add<T>( _function ) );
  }

  /**
   * @brief Logger operator << for std::any.
   * @param _logger   Logger.
   * @param _input   Input std::any.
   * @return Logger with output.
   */
  inline Logger &operator<<( Logger &_logger,
                             const std::any &_input ) {

    const bool saveState = _logger.autoSpace();
    visit( _logger.nospace(), _input );
    _logger.setAutoSpace( saveState );
    return _logger.maybeSpace();
  }
}
