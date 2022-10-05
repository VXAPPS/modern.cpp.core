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
#include <chrono>
#include <functional>
#include <iomanip>
#include <list>
#include <map>
#include <optional>
#include <ostream>
#include <ratio>
#include <set>
#include <source_location.hpp>
#include <string>
#include <string_view>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility> // std::pair
#include <variant>
#include <vector>

/* magic_enum */
#include <magic_enum.hpp>

/* modern.cpp.core */
#include <Demangle.h>
#include <Singleton.h>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx::logger {

  /**
   * @brief The Severity enum.
   */
  enum class Severity {

    Verbose, /**< Verbose level. */
    Debug,   /**< Debug level. */
    Info,    /**< Info level. */
    Warning, /**< Warning level. */
    Error,   /**< Error level. */
    Fatal    /**< Fatal error level. */
  };

  /**
   * @brief The Flags enum.
   */
  enum class Flags {

    None,   /**< No flags. */
    Space,  /**< Auto spaces. */
    Quotes, /**< Auto qoutes. */
    Types   /**< Auto types. */
  };

  /**
   * @brief The Path enum.
   */
  enum class Path {

    Absolute, /**< Complete path. */
    Relative, /**< Absolute path to project. */
    Filename  /**< Only the filename. */
  };

  class Configuration : public Singleton<Configuration> {

  public:
    [[nodiscard]] inline std::string filename() const noexcept { return m_filename; }

    void setFilename( const std::string &_filename ) noexcept { m_filename = _filename; }

    void setFlags() noexcept {}

    [[nodiscard]] inline bool autoSpace() const noexcept { return m_autoSpace; }

    inline void setAutoSpace( bool _autoSpace ) noexcept { m_autoSpace = _autoSpace; }

    [[nodiscard]] inline bool autoQuotes() const noexcept { return m_autoQuotes; }

    inline void setAutoQuotes( bool _autoQuotes ) noexcept { m_autoQuotes = _autoQuotes; }

    [[nodiscard]] inline Severity avoidLogBelow() const noexcept { return m_avoidLogBelow; }

    inline void setAvoidLogBelow( Severity _severity ) noexcept { m_avoidLogBelow = _severity; }

  private:
    bool m_autoSpace = true;
    bool m_autoQuotes = true;

    Severity m_avoidLogBelow = Severity::Warning;
    std::string m_filename {};
  };

  class Logger {

  public:
    /**
     * @brief Default constructor for Logger.
     * @param _severity   Severity type.
     * @param _location   Source location informations.
     */
    explicit Logger( Severity _severity = Severity::Debug,
                     const std::source_location &_location = std::source_location::current() ) noexcept;

    /**
     * @brief Default destructor for Logger.
     */
    ~Logger() noexcept;

    /**
     * @brief @~english Delete copy constructor. @~german Entfernt den kopierenden Konstruktor.
     */
    Logger( const Logger & ) = delete;

    /**
     * @brief @~english Delete move constructor. @~german Entfernt den verschobenen Konstruktor.
     */
    Logger( Logger && ) = delete;

    /**
     * @brief @~english Delete copy assign. @~german Entfernt die kopierte Zuweisung.
     * @return @~english Nothing. @~german Keine Rückgabe.
     */
    Logger &operator=( const Logger & ) = delete;

    /**
     * @brief @~english Delete move assign. @~german Entfernt die verschobene Zuweisung.
     * @return @~english Nothing. @~german Keine Rückgabe.
     */
    Logger &operator=( Logger && ) = delete;

    Logger &logger() noexcept { return *this; }

    void printChar( char _input ) noexcept;

    void printString( std::string_view _input ) noexcept;

    [[nodiscard]] inline bool autoSpace() const noexcept { return m_autoSpace; }

    inline void setAutoSpace( bool _autoSpace ) noexcept { m_autoSpace = _autoSpace; }

    [[nodiscard]] inline bool autoQuotes() const noexcept { return m_autoQuotes; }

    inline void setAutoQuotes( bool _autoQuotes ) noexcept { m_autoQuotes = _autoQuotes; }

    inline void flush() noexcept { m_stream.flush(); }

    inline Logger &space() noexcept {

      m_autoSpace = true;
      m_stream << ' ';
      return *this;
    }

    inline Logger &nospace() noexcept {

      m_autoSpace = false;
      return *this;
    }

    inline Logger &maybeSpace() noexcept {

      if ( m_autoSpace ) { m_stream << ' '; }
      return *this;
    }

    inline std::ostream &stream() { return m_stream; }

    inline Logger &operator<<( bool _input ) noexcept {

      m_stream << ( _input ? "true" : "false" );
      return maybeSpace();
    }

    inline Logger &operator<<( char _input ) noexcept {

      printChar( _input );
      return maybeSpace();
    }

    inline Logger &operator<<( int _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }

#if !defined _MSC_VER || defined _MSC_VER && _MSC_VER >= 1920
    inline Logger &operator<<( unsigned int _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }
#endif

    inline Logger &operator<<( std::size_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }

#ifdef __APPLE__
    inline Logger &operator<<( std::int64_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }

    inline Logger &operator<<( std::uint64_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }
#endif

    inline Logger &operator<<( float _input ) noexcept {

      const std::streamsize saveState = m_stream.precision();
      m_stream.precision( std::numeric_limits<float>::max_digits10 );
      m_stream << _input;
      m_stream.precision( saveState );
      return maybeSpace();
    }

    inline Logger &operator<<( double _input ) noexcept {

      const std::streamsize saveState = m_stream.precision();
      m_stream.precision( std::numeric_limits<double>::max_digits10 );
      m_stream << _input;
      m_stream.precision( saveState );
      return maybeSpace();
    }

    inline Logger &operator<<( const char *_input ) noexcept {

      printString( _input );
      return maybeSpace();
    }

    inline Logger &operator<<( std::string_view _input ) noexcept {

      printString( _input );
      m_stream << 's' << 'v';
      return maybeSpace();
    }

    inline Logger &operator<<( const std::string &_input ) noexcept {

      printString( _input );
      return maybeSpace();
    }

    template <typename T, typename Ratio = std::ratio<1>>
    inline Logger &operator<<( const std::chrono::duration<T, Ratio> &_input ) noexcept {

      Ratio ratio;
      std::string_view literal {};
      constexpr int hourInSeconds = 3600;
      constexpr int minuteInSesonds = 60;
      if constexpr ( ratio.num == std::ratio<hourInSeconds, 1>::num && ratio.den == std::ratio<hourInSeconds, 1>::den ) { literal = "h"; }
      else if constexpr ( ratio.num == std::ratio<minuteInSesonds, 1>::num && ratio.den == std::ratio<minuteInSesonds, 1>::den ) { literal = "min"; }
      else if constexpr ( ratio.num == std::ratio<1, 1>::num && ratio.den == std::ratio<1, 1>::den ) { literal = "s"; }
      else if constexpr ( ratio.num == std::milli::num && ratio.den == std::milli::den ) { literal = "ms"; }
      else if constexpr ( ratio.num == std::micro::num && ratio.den == std::micro::den ) { literal = "us"; }
      else if constexpr ( ratio.num == std::nano::num && ratio.den == std::nano::den ) { literal = "ns"; }

      m_stream << _input.count() << ' ';

      if ( literal.empty() ) { m_stream << "unsupported " << '(' << ratio.num << '/' << ratio.den << ')'; }
      else { m_stream << literal; }
      return maybeSpace();
    }

    Logger &operator<<( std::time_t _input ) noexcept;

    inline Logger &operator<<( const void *_input ) noexcept {

      _input == nullptr ? m_stream << "(nullptr)" : m_stream << '(' << _input << ')';
      return maybeSpace();
    }

    inline Logger &operator<<( [[maybe_unused]] std::nullptr_t _input ) noexcept {

      m_stream << "(nullptr_t)";
      return maybeSpace();
    }

    inline Logger &operator<<( [[maybe_unused]] std::nullopt_t _input ) noexcept {

      m_stream << "(nullopt_t)";
      return maybeSpace();
    }

    template <typename Tuple>
    void printTupleReal( [[maybe_unused]] std::size_t _current,
                         [[maybe_unused]] const Tuple &_tuple,
                         [[maybe_unused]] typename std::tuple_size<Tuple>::type _size ) noexcept {}

    template <std::size_t _pos, typename Tuple, typename = std::enable_if_t<std::tuple_size<Tuple>::value != _pos>>
    void printTupleReal( std::size_t _current,
                         const Tuple &_tuple,
                         [[maybe_unused]] std::integral_constant<std::size_t, _pos> _integral ) noexcept {

      if ( _current == _pos ) {

        const bool saveState = autoSpace();
        nospace() << std::get<_pos>( _tuple );
        setAutoSpace( saveState );
      }
      else {

        printTupleReal( _current, _tuple, std::integral_constant<std::size_t, _pos + 1>() );
      }
    }

    template <typename Tuple>
    void printTuple( std::size_t _pos,
                     const Tuple &_tuple ) noexcept {

      printTupleReal( _pos, _tuple, std::integral_constant<std::size_t, 0>() );
    }

    template <typename Variant>
    void printVariantReal( [[maybe_unused]] std::size_t _current,
                           [[maybe_unused]] const Variant &_variant,
                           [[maybe_unused]] typename std::variant_size<Variant>::type _size ) noexcept {}

    template <std::size_t _pos, typename Variant, typename = std::enable_if_t<std::variant_size<Variant>::value != _pos>>
    void printVariantReal( std::size_t _current,
                           const Variant &_variant,
                           [[maybe_unused]] std::integral_constant<std::size_t, _pos> _integral ) noexcept {

      if ( _current == _pos ) {

        try {

          const bool saveState = autoSpace();
          nospace() << std::get<_pos>( _variant );
          setAutoSpace( saveState );
        }
        catch ( [[maybe_unused]] const std::bad_variant_access &_exception ) {

          /* Nothing to do here. */
        }
      }
      else {

        printVariantReal( _current, _variant, std::integral_constant<std::size_t, _pos + 1>() );
      }
    }

    template <typename Variant>
    void printVariant( std::size_t _pos,
                       const Variant &_variant ) noexcept {

      printVariantReal( _pos, _variant, std::integral_constant<std::size_t, 0>() );
    }

  private:
    bool m_autoSpace = true;
    bool m_autoQuotes = true;

    Severity m_severity = Severity::Debug;
    Path m_locationPath = Path::Filename;

    std::source_location m_location;
    std::ostream m_stream;

    /**
     * @brief Create timestamp.
     * @return A timestamp.
     */
    std::string timestamp() const noexcept;

    /**
     * @brief Create severity output.
     * @param _severity   Which severity to generate?
     * @return The formatted severity.
     */
    std::string severity( Severity _severity ) const noexcept;
  };

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
    func checkComma = []() {};
    func printComma = [ &_logger ]() { _logger.stream() << ',' << ' '; };
    func noPrint = [ & ]() { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _list ).name() ) << ' ' << '{';
    for ( const auto &value : _list ) {

      checkComma();
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
    func checkComma = []() {};
    func printComma = [ &_logger ]() { _logger.stream() << ',' << ' '; };
    func noPrint = [ & ]() { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _map ).name() ) << ' ' << '{';
    for ( const auto &[ key, value ] : _map ) {

      checkComma();
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
    func checkComma = []() {};
    func printComma = [ &_logger ]() { _logger.stream() << ',' << ' '; };
    func noPrint = [ & ]() { checkComma = printComma; };
    checkComma = noPrint;

    _logger.stream() << demangleExtreme( typeid( _tuple ).name() ) << ' ' << '{';
    std::size_t tupleSize = std::tuple_size_v<T>;
    for ( std::size_t pos = 0; pos < tupleSize; pos++ ) {

      checkComma();
      _logger.printTuple( pos, _tuple );
    }
    _logger.stream() << '}';
    return _logger.maybeSpace();
  }

  /* template <typename T>
  void helper( [[maybe_unused]] Logger &_logger ) noexcept {}

  template <typename T, typename First, typename... Rest>
  void helper( Logger &_logger ) noexcept {

    _logger << demangleExtreme( typeid( First ).name() );
    helper<T, Rest...>( _logger );
  } */

  template <typename... Ts>
  inline Logger &operator<<( Logger &_logger,
                             const std::tuple<Ts...> &_values ) noexcept {

    //    helper<void, Ts...>( _logger );
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

    //    helper<void, Ts...>( _logger );
    return printVariant( _logger, _values );
  }

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
  const std::unordered_map<std::type_index, std::function<void( Logger &_logger, const std::any & )>> visitors {

    add<bool>( []( Logger &_logger, bool _input ) { _logger << _input; } ),
    add<char>( []( Logger &_logger, char _input ) { _logger << _input; } ),
    add<int>( []( Logger &_logger, int _input ) { _logger << _input; } ),
    add<unsigned int>( []( Logger &_logger, unsigned int _input ) { _logger << _input; } ),
    add<std::size_t>( []( Logger &_logger, std::size_t _input ) { _logger << _input; } ),
    add<float>( []( Logger &_logger, float _input ) { _logger << _input; } ),
    add<double>( []( Logger &_logger, double _input ) { _logger << _input; } ),
    add<const char *>( []( Logger &_logger, const char *_input ) { _logger << _input; } ),
    add<std::string_view>( []( Logger &_logger, std::string_view _input ) { _logger << _input; } ),
    add<std::string>( []( Logger &_logger, const std::string &_input ) { _logger << _input; } ),
    add<std::list<bool>>( []( Logger &_logger, const std::list<bool> &_input ) { _logger << _input; } ),
    add<std::list<char>>( []( Logger &_logger, const std::list<char> &_input ) { _logger << _input; } ),
    add<std::list<int>>( []( Logger &_logger, const std::list<int> &_input ) { _logger << _input; } ),
    add<std::list<unsigned int>>( []( Logger &_logger, const std::list<unsigned int> &_input ) { _logger << _input; } ),
    add<std::list<std::size_t>>( []( Logger &_logger, const std::list<std::size_t> &_input ) { _logger << _input; } ),
    add<std::list<float>>( []( Logger &_logger, const std::list<float> &_input ) { _logger << _input; } ),
    add<std::list<double>>( []( Logger &_logger, const std::list<double> &_input ) { _logger << _input; } ),
    add<std::list<const char *>>( []( Logger &_logger, const std::list<const char *> &_input ) { _logger << _input; } ),
    add<std::list<std::string_view>>( []( Logger &_logger, const std::list<std::string_view> &_input ) { _logger << _input; } ),
    add<std::list<std::string>>( []( Logger &_logger, const std::list<std::string> &_input ) { _logger << _input; } ),
    add<std::set<bool>>( []( Logger &_logger, const std::set<bool> &_input ) { _logger << _input; } ),
    add<std::set<char>>( []( Logger &_logger, const std::set<char> &_input ) { _logger << _input; } ),
    add<std::set<int>>( []( Logger &_logger, const std::set<int> &_input ) { _logger << _input; } ),
    add<std::set<unsigned int>>( []( Logger &_logger, const std::set<unsigned int> &_input ) { _logger << _input; } ),
    add<std::set<std::size_t>>( []( Logger &_logger, const std::set<std::size_t> &_input ) { _logger << _input; } ),
    add<std::set<float>>( []( Logger &_logger, const std::set<float> &_input ) { _logger << _input; } ),
    add<std::set<double>>( []( Logger &_logger, const std::set<double> &_input ) { _logger << _input; } ),
    add<std::set<const char *>>( []( Logger &_logger, const std::set<const char *> &_input ) { _logger << _input; } ),
    add<std::set<std::string_view>>( []( Logger &_logger, const std::set<std::string_view> &_input ) { _logger << _input; } ),
    add<std::set<std::string>>( []( Logger &_logger, const std::set<std::string> &_input ) { _logger << _input; } ),
    // MAC found that ambiguous...    add<std::vector<bool>>( []( Logger & _logger, const std::vector<bool> &_input ) { _logger << _input; } ),
    add<std::vector<char>>( []( Logger &_logger, const std::vector<char> &_input ) { _logger << _input; } ),
    add<std::vector<int>>( []( Logger &_logger, const std::vector<int> &_input ) { _logger << _input; } ),
    add<std::vector<unsigned int>>( []( Logger &_logger, const std::vector<unsigned int> &_input ) { _logger << _input; } ),
    add<std::vector<std::size_t>>( []( Logger &_logger, const std::vector<std::size_t> &_input ) { _logger << _input; } ),
    add<std::vector<float>>( []( Logger &_logger, const std::vector<float> &_input ) { _logger << _input; } ),
    add<std::vector<double>>( []( Logger &_logger, const std::vector<double> &_input ) { _logger << _input; } ),
    add<std::vector<const char *>>( []( Logger &_logger, const std::vector<const char *> &_input ) { _logger << _input; } ),
    add<std::vector<std::string_view>>( []( Logger &_logger, const std::vector<std::string_view> &_input ) { _logger << _input; } ),
    add<std::vector<std::string>>( []( Logger &_logger, const std::vector<std::string> &_input ) { _logger << _input; } ),
    // VC2017 issue    add<void>( []( Logger & _logger, [[maybe_unused]] void *_input ) { _logger << _input; } ),
  };
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

  inline void visit( Logger &_logger,
                     const std::any &_any ) noexcept {

    if ( const auto iterator = visitors.find( std::type_index( _any.type() ) ); iterator != visitors.cend() ) {

      iterator->second( _logger, _any );
    }
    else {

      _logger.stream() << "unregistered: " << demangleExtreme( _any.type().name() );
    }
  }

  template <typename T, typename Function>
  inline void registerVisitor( const Function &_function ) noexcept {

    visitors.insert( add<T>( _function ) );
  }

  inline Logger &operator<<( Logger &_logger,
                             const std::any &_input ) noexcept {

    const bool saveState = _logger.autoSpace();
    visit( _logger.nospace(), _input );
    _logger.setAutoSpace( saveState );
    return _logger.maybeSpace();
  }

  /* MAGIC ENUM */
  template <typename E, magic_enum::detail::enable_if_t<E, int> = 0>
  inline Logger &operator<<( Logger &_logger,
                             E _value ) noexcept {

    using D = std::decay_t<E>;
    using U = magic_enum::underlying_type_t<D>;

    if constexpr ( magic_enum::detail::supported<D>::value ) {

      if ( const auto name = magic_enum::enum_flags_name<D>( _value ); !name.empty() ) {

        _logger.stream() << name;
        return _logger.maybeSpace();
      }
    }
    _logger.stream() << static_cast<U>( _value );
    return _logger.maybeSpace();
  }

  template <typename E, magic_enum::detail::enable_if_t<E, int> = 0>
  inline Logger &operator<<( Logger &_logger, magic_enum::optional<E> _value ) noexcept {

    _value ? _logger << *_value : _logger.stream() << "(nullopt)";
    return _logger.maybeSpace();
  }
}

#define logVerbose vx::logger::Logger( vx::logger::Severity::Verbose ).logger
#define logDebug vx::logger::Logger( vx::logger::Severity::Debug ).logger
#define logInfo vx::logger::Logger( vx::logger::Severity::Info ).logger
#define logWarning vx::logger::Logger( vx::logger::Severity::Warning ).logger
#define logError vx::logger::Logger( vx::logger::Severity::Error ).logger
#define logFatal vx::logger::Logger( vx::logger::Severity::Fatal ).logger
