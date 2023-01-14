#pragma once

/* c header */
#include <cstdint>

/* stl header */
#include <string_view>

namespace std {

  struct source_location {

  public:
#if defined __clang__ && __clang_major__ >= 9 || defined _MSC_VER && _MSC_VER >= 1920
    static constexpr source_location current( std::string_view filename = __builtin_FILE(),
                                              std::string_view functionName = __builtin_FUNCTION(),
                                              const std::uint_least32_t lineNumber = __builtin_LINE(),
                                              const std::uint_least32_t columnOffset = __builtin_COLUMN() ) noexcept
#else
  #if defined __GNUC__ && ( __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ >= 8 ) )
    static constexpr source_location current( std::string_view filename = __builtin_FILE(),
                                              std::string_view functionName = __builtin_FUNCTION(),
                                              const std::uint_least32_t lineNumber = __builtin_LINE(),
                                              const std::uint_least32_t columnOffset = 0 ) noexcept
  #else
    static constexpr source_location current( std::string_view filename = "unsupported",
                                              std::string_view functionName = "unsupported",
                                              const std::uint_least32_t lineNumber = 0,
                                              const std::uint_least32_t columnOffset = 0 ) noexcept
  #endif
#endif
    {
      return { filename, functionName, lineNumber, columnOffset };
    }

    source_location( const source_location & ) = default;
    source_location( source_location && ) = default;

    [[nodiscard]] constexpr std::string_view file_name() const noexcept {

      return m_filename;
    }

    [[nodiscard]] constexpr std::string_view function_name() const noexcept {

      return m_functionName;
    }

    [[nodiscard]] constexpr std::uint_least32_t line() const noexcept {

      return m_lineNumber;
    }

    [[nodiscard]] constexpr std::uint_least32_t column() const noexcept {

      return m_columnOffset;
    }

  private:
    constexpr source_location( std::string_view _filename,
                               std::string_view _functionName,
                               const std::uint_least32_t _lineNumber,
                               const std::uint_least32_t _columnOffset ) noexcept
      : m_filename( _filename ),
        m_functionName( _functionName ),
        m_lineNumber( _lineNumber ),
        m_columnOffset( _columnOffset ) {}

    std::string_view m_filename;
    std::string_view m_functionName;
    const std::uint_least32_t m_lineNumber;
    const std::uint_least32_t m_columnOffset;
  };
}
