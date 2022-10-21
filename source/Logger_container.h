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
#include <any>
#include <array>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility> // std::pair
#include <variant>
#include <vector>

/* local header */
#include "Demangle.h"
#include "Logger.h"

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx::logger {

  template <typename T>
  Logger &operator<<( Logger &_logger,
                      const std::optional<T> &_optional ) noexcept {

    _logger.stream() << demangleExtreme( typeid( _optional ).name() ) << ' ';
    if ( _optional ) {

      const bool saveState = _logger.autoSpace();
      _logger.nospace() << *_optional;
      _logger.setAutoSpace( saveState );
    }
    else {

      _logger.stream() << "(nullopt)";
    }
    return _logger.maybeSpace();
  }

  template <typename Key, typename T>
  Logger &operator<<( Logger &_logger,
                      const std::pair<Key, T> &_pair ) noexcept {

    _logger.stream() << /* demangleExtreme( typeid( _pair ).name() ) << ' ' << */ '{';
    const bool saveState = _logger.autoSpace();
    _logger.nospace() << _pair.first;
    _logger.stream() << ',' << ' ';
    _logger << _pair.second;
    _logger.setAutoSpace( saveState );
    _logger.stream() << '}';
    return _logger.maybeSpace();
  }

  template <typename List>
  Logger &printList( Logger &_logger,
                     const List &_list ) noexcept {

    using func = std::function<void( void )>;
    func checkComma {};
    const func printComma = [ &_logger ]() noexcept { _logger.stream() << ',' << ' '; };
    const func noPrint = [ &checkComma, &printComma ]() noexcept { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _list ).name() ) << ' ' << '{';
    for ( const auto &value : _list ) {

      try {

        checkComma();
      }
      catch ( [[maybe_unused]] const std::bad_function_call &_exception ) {

        /* Nothing to do here, the delimeter is not the most important thing here. */
      }
      const bool saveState = _logger.autoSpace();
      _logger.nospace() << value;
      _logger.setAutoSpace( saveState );
    }
    _logger.stream() << '}';
    return _logger.maybeSpace();
  }

  template <typename T, std::size_t N>
  inline Logger &operator<<( Logger &_logger,
                             const std::array<T, N> &_array ) noexcept {

    return printList( _logger, _array );
  }

  template <typename T, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::list<T, Alloc> &_list ) noexcept {

    return printList( _logger, _list );
  }

  template <typename T, typename Compare, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::set<T, Compare, Alloc> &_set ) noexcept {

    return printList( _logger, _set );
  }

  template <typename T, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::vector<T, Alloc> &_vector ) noexcept {

    return printList( _logger, _vector );
  }

  template <typename T>
  Logger &printMap( Logger &_logger,
                    const T &_map ) noexcept {

    using func = std::function<void( void )>;
    func checkComma {};
    const func printComma = [ &_logger ]() noexcept { _logger.stream() << ',' << ' '; };
    const func noPrint = [ &checkComma, &printComma ]() noexcept { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _map ).name() ) << ' ' << '{';
    for ( const auto &[ key, value ] : _map ) {

      try {

        checkComma();
      }
      catch ( [[maybe_unused]] const std::bad_function_call &_exception ) {

        /* Nothing to do here, the delimeter is not the most important thing here. */
      }
      _logger.stream() << '{';
      const bool saveState = _logger.autoSpace();
      _logger.nospace() << key;
      _logger.stream() << ',' << ' ';
      _logger << value;
      _logger.setAutoSpace( saveState );
      _logger.stream() << '}';
    }
    _logger.stream() << '}';
    return _logger.maybeSpace();
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::map<Key, T, Compare, Alloc> &_map ) noexcept {

    return printMap( _logger, _map );
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::multimap<Key, T, Compare, Alloc> &_map ) noexcept {

    return printMap( _logger, _map );
  }

  template <typename Key, typename T, typename Compare, typename Alloc>
  inline Logger &operator<<( Logger &_logger,
                             const std::unordered_map<Key, T, Compare, Alloc> &_map ) noexcept {

    return printMap( _logger, _map );
  }

  template <typename T>
  Logger &printTuple( Logger &_logger,
                      const T &_tuple ) noexcept {

    using func = std::function<void( void )>;
    func checkComma {};
    const func printComma = [ &_logger ]() noexcept { _logger.stream() << ',' << ' '; };
    const func noPrint = [ &checkComma, &printComma ]() noexcept { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _tuple ).name() ) << ' ' << '{';
    std::size_t tupleSize = std::tuple_size_v<T>;
    for ( std::size_t pos = 0; pos < tupleSize; pos++ ) {

      try {

        checkComma();
      }
      catch ( [[maybe_unused]] const std::bad_function_call &_exception ) {

        /* Nothing to do here, the delimeter is not the most important thing here. */
      }
      _logger.printTuple( pos, _tuple );
    }
    _logger.stream() << '}';
    return _logger.maybeSpace();
  }

  template <typename... Ts>
  inline Logger &operator<<( Logger &_logger,
                             const std::tuple<Ts...> &_values ) noexcept {

    return printTuple( _logger, _values );
  }

  template <typename T>
  Logger &printVariant( Logger &_logger,
                        const T &_variant ) noexcept {

    _logger.stream() << demangleExtreme( typeid( _variant ).name() ) << ' ';
    std::size_t variantSize = std::variant_size_v<T>;
    for ( std::size_t pos = 0; pos < variantSize; pos++ ) {

      _logger.printVariant( pos, _variant );
    }
    return _logger.maybeSpace();
  }

  template <typename... Ts>
  inline Logger &operator<<( Logger &_logger,
                             const std::variant<Ts...> &_values ) noexcept {

    return printVariant( _logger, _values );
  }
}
