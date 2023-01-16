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
 * @brief vx (VX APPS) logger namespace.
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

  /**
   * @brief Logger configuration.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class Configuration : public Singleton<Configuration> {

  public:
    /**
     * @brief Get filename.
     * @return Filename.
     */
    [[nodiscard]] inline std::string filename() const { return m_filename; }

    /**
     * @brief Set filename.
     * @param _filename   The filename.
     */
    void setFilename( std::string_view _filename ) { m_filename = _filename; }

    /**
     * @brief Is auto space enabled?
     * @return True, if auto space is enabled - otherwise false.
     */
    [[nodiscard]] inline bool autoSpace() const noexcept { return m_autoSpace; }

    /**
     * @brief Set auto space.
     * @param _autoSpace   True, to enable auto space.
     */
    inline void setAutoSpace( bool _autoSpace ) noexcept { m_autoSpace = _autoSpace; }

    /**
     * @brief Is auto quotes enabled?
     * @return True, auto quotes are enabled - otherwise false.
     */
    [[nodiscard]] inline bool autoQuotes() const noexcept { return m_autoQuotes; }

    /**
     * @brief Set auto quotes.
     * @param _autoQuotes   True, to enable auto quotes.
     */
    inline void setAutoQuotes( bool _autoQuotes ) noexcept { m_autoQuotes = _autoQuotes; }

    /**
     * @brief Avoid log below loglevel.
     * @return Current loglevel.
     */
    [[nodiscard]] inline Severity avoidLogBelow() const noexcept { return m_avoidLogBelow; }

    /**
     * @brief Set avoid log below.
     * @param _severity   Logging below this level will not written.
     */
    inline void setAvoidLogBelow( Severity _severity ) noexcept { m_avoidLogBelow = _severity; }

  private:
    /**
     * @brief Member for auto space.
     */
    bool m_autoSpace = true;

    /**
     * @brief Member for auto quotes.
     */
    bool m_autoQuotes = true;

    /**
     * @brief Member for avoid log level.
     */
    Severity m_avoidLogBelow = Severity::Warning;

    /**
     * @brief Member for filename.
     */
    std::string m_filename {};
  };

  /**
   * @brief Logger class.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class Logger {

  public:
    /**
     * @brief Default constructor for Logger.
     * @param _severity   Severity type.
     * @param _location   Source location informations.
     */
    explicit Logger( Severity _severity = Severity::Debug,
                     const std::source_location &_location = std::source_location::current() );

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

    /**
     * @brief Get logger reference.
     * @return Logger with output.
     */
    Logger &logger() noexcept { return *this; }

    /**
     * @brief Print char.
     * @param _input   Char.
     */
    void printChar( std::int8_t _input ) noexcept;

    /**
     * @brief Print string.
     * @param _input   String.
     */
    void printString( std::string_view _input );

    /**
     * @brief Is auto space enabled?
     * @return True, if auto space is enabled - otherwise false.
     */
    [[nodiscard]] inline bool autoSpace() const noexcept { return m_autoSpace; }

    /**
     * @brief Set auto space.
     * @param _autoSpace   True, to enable auto space.
     */
    inline void setAutoSpace( bool _autoSpace ) noexcept { m_autoSpace = _autoSpace; }

    /**
     * @brief Is auto quotes enabled?
     * @return True, auto quotes are enabled - otherwise false.
     */
    [[nodiscard]] inline bool autoQuotes() const noexcept { return m_autoQuotes; }

    /**
     * @brief Set auto quotes.
     * @param _autoQuotes   True, to enable auto quotes.
     */
    inline void setAutoQuotes( bool _autoQuotes ) noexcept { m_autoQuotes = _autoQuotes; }

    /**
     * @brief Flush the stream.
     */
    inline void flush() noexcept { m_stream.flush(); }

    /**
     * @brief Enable auto space and print one.
     * @return Logger with output.
     */
    inline Logger &space() noexcept {

      m_autoSpace = true;
      m_stream << ' ';
      return *this;
    }

    /**
     * @brief Disable auto space.
     * @return Logger with output.
     */
    inline Logger &nospace() noexcept {

      m_autoSpace = false;
      return *this;
    }

    /**
     * @brief If auto space is enabled print a space.
     * @return Logger with output.
     */
    inline Logger &maybeSpace() noexcept {

      if ( m_autoSpace ) { m_stream << ' '; }
      return *this;
    }

    /**
     * @brief Direct access to logging stream.
     * @return Stream access.
     */
    inline std::ostream &stream() { return m_stream; }

    /**
     * @brief Logger operator << for bool.
     * @param _input   Input bool.
     * @return Logger with output.
     */
    inline Logger &operator<<( bool _input ) noexcept {

      m_stream << ( _input ? "true" : "false" );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::int8_t.
     * @param _input   Input std::int8_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::int8_t _input ) noexcept {

      printChar( _input );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::int32_t.
     * @param _input   Input std::int32_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::int32_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }

#if !defined _MSC_VER || defined _MSC_VER && _MSC_VER >= 1920
    /**
     * @brief Logger operator << for std::uint32_t.
     * @param _input   Input std::uint32_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::uint32_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }
#endif

#if defined _WIN32 && !defined _WIN64
    // bad, but we just need to drop that out on 32bit Windows.
#else
    /**
     * @brief Logger operator << for std::size_t.
     * @param _input   Input std::size_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::size_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }
#endif

#ifdef __APPLE__
    /**
     * @brief Logger operator << for std::int64_t.
     * @param _input   Input std::int64_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::int64_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::uint64_t.
     * @param _input   Input std::uint64_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::uint64_t _input ) noexcept {

      m_stream << _input;
      return maybeSpace();
    }
#endif

    /**
     * @brief Logger operator << for float.
     * @param _input   Input float.
     * @return Logger with output.
     */
    inline Logger &operator<<( float _input ) noexcept {

      const std::streamsize saveState = m_stream.precision();
      m_stream.precision( std::numeric_limits<float>::max_digits10 );
      m_stream << _input;
      m_stream.precision( saveState );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for double.
     * @param _input   Input double.
     * @return Logger with output.
     */
    inline Logger &operator<<( double _input ) noexcept {

      const std::streamsize saveState = m_stream.precision();
      m_stream.precision( std::numeric_limits<double>::max_digits10 );
      m_stream << _input;
      m_stream.precision( saveState );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for const char *.
     * @param _input   Input const char *.
     * @return Logger with output.
     */
    inline Logger &operator<<( const char *_input ) noexcept {

      printString( _input );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::string_view.
     * @param _input   Input std::string_view.
     * @return Logger with output.
     */
    inline Logger &operator<<( std::string_view _input ) noexcept {

      printString( _input );
      m_stream << 's' << 'v';
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::string.
     * @param _input   Input std::string.
     * @return Logger with output.
     */
    inline Logger &operator<<( const std::string &_input ) noexcept {

      printString( _input );
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::chrono::duration.
     * @param _input   Input std::chrono::duration.
     * @return Logger with output.
     */
    template <typename T, typename Ratio = std::ratio<1>>
    inline Logger &operator<<( const std::chrono::duration<T, Ratio> &_input ) noexcept {

      Ratio ratio;
      std::string_view literal {};
      constexpr std::int32_t hourInSeconds = 3600;
      constexpr std::int32_t minuteInSesonds = 60;
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

    /**
     * @brief Logger operator << for std::time_t.
     * @param _input   Input std::time_t.
     * @return Logger with output.
     */
    Logger &operator<<( std::time_t _input ) noexcept;

    /**
     * @brief Logger operator << for void *.
     * @param _input   Input void *.
     * @return Logger with output.
     */
    inline Logger &operator<<( const void *_input ) noexcept { // NOSONAR redundant is needed.

      _input == nullptr ? m_stream << "(nullptr)" : m_stream << '(' << _input << ')';
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::nullptr_t.
     * @param _input   Input std::nullptr_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( [[maybe_unused]] std::nullptr_t _input ) noexcept {

      m_stream << "(nullptr_t)";
      return maybeSpace();
    }

    /**
     * @brief Logger operator << for std::nullopt_t.
     * @param _input   Input std::nullopt_t.
     * @return Logger with output.
     */
    inline Logger &operator<<( [[maybe_unused]] std::nullopt_t _input ) noexcept {

      m_stream << "(nullopt_t)";
      return maybeSpace();
    }

    /**
     * @brief Internal print std::tuple.
     * @param _current   Current tuple position.
     * @param _tuple   Tuple type input.
     * @param _size   Tuple size.
     */
    template <typename Tuple>
    void printTupleReal( [[maybe_unused]] std::size_t _current,
                         [[maybe_unused]] const Tuple &_tuple,
                         [[maybe_unused]] typename std::tuple_size<Tuple>::type _size ) const noexcept { /* empty */ }

    /**
     * @brief Internal print std::tuple.
     * @param _current   Current tuple position.
     * @param _tuple   Tuple type input.
     * @param _integral   Integral position to access it directly.
     */
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

    /**
     * @brief Output std::tuple.
     * @param _pos   Starting tuple  position.
     * @param _tuple   Tuple type input.
     */
    template <typename Tuple>
    void printTuple( std::size_t _pos,
                     const Tuple &_tuple ) noexcept {

      printTupleReal( _pos, _tuple, std::integral_constant<std::size_t, 0>() );
    }

    /**
     * @brief Internal print std::variant.
     * @param _current   Current variant position.
     * @param _variant   Variant type input.
     * @param _size   Variant size.
     */
    template <typename Variant>
    void printVariantReal( [[maybe_unused]] std::size_t _current,
                           [[maybe_unused]] const Variant &_variant,
                           [[maybe_unused]] typename std::variant_size<Variant>::type _size ) const noexcept { /* empty */ }

    /**
     * @brief Internal print std::variant.
     * @param _current   Current variant position.
     * @param _variant   Variant typeinput.
     * @param _integral   Integral position to access it directly.
     */
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
        catch ( const std::bad_variant_access &_exception ) {

          /* Nothing to do here. */
          stream() << "bad_variant_access " << _exception.what();
        }
      }
      else {

        printVariantReal( _current, _variant, std::integral_constant<std::size_t, _pos + 1>() );
      }
    }

    /**
     * @brief Output std::variant.
     * @param _pos   Starting variant position.
     * @param _variant   Variant type input.
     */
    template <typename Variant>
    void printVariant( std::size_t _pos,
                       const Variant &_variant ) noexcept {

      printVariantReal( _pos, _variant, std::integral_constant<std::size_t, 0>() );
    }

  private:
    /**
     * @brief Automatically sapce next argument.
     */
    bool m_autoSpace = true;

    /**
     * @brief Automatically quote strings.
     */
    bool m_autoQuotes = true;

    /**
     * @brief Member fpr severity.
     */
    Severity m_severity = Severity::Debug;

    /**
     * @brief Member for location path configuration.
     */
    Path m_locationPath = Path::Filename;

    /**
     * @brief Member for source location.
     */
    std::source_location m_location;

    /**
     * @brief Member for stream.
     */
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
    std::string severity( Severity _severity ) const;
  };
}

#define logVerbose vx::logger::Logger( vx::logger::Severity::Verbose ).logger
#define logDebug vx::logger::Logger( vx::logger::Severity::Debug ).logger
#define logInfo vx::logger::Logger( vx::logger::Severity::Info ).logger
#define logWarning vx::logger::Logger( vx::logger::Severity::Warning ).logger
#define logError vx::logger::Logger( vx::logger::Severity::Error ).logger
#define logFatal vx::logger::Logger( vx::logger::Severity::Fatal ).logger
