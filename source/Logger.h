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
#include <chrono>
#include <optional>
#include <ostream>
#include <ratio>
#include <source_location.hpp>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>

/* local header */
#include "Singleton.h"

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
                         [[maybe_unused]] typename std::tuple_size<Tuple>::type _size ) const noexcept { /* empty */
    }

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
                           [[maybe_unused]] typename std::variant_size<Variant>::type _size ) const noexcept { /* empty */
    }

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
          // logFatal() << "bad_variant_access" << _exception.what();
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
}

#define logVerbose vx::logger::Logger( vx::logger::Severity::Verbose ).logger
#define logDebug vx::logger::Logger( vx::logger::Severity::Debug ).logger
#define logInfo vx::logger::Logger( vx::logger::Severity::Info ).logger
#define logWarning vx::logger::Logger( vx::logger::Severity::Warning ).logger
#define logError vx::logger::Logger( vx::logger::Severity::Error ).logger
#define logFatal vx::logger::Logger( vx::logger::Severity::Fatal ).logger
