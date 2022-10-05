#pragma once

/* c header */
#include <cstdint>

/* stl header */
#include <string_view>

namespace std {

  struct source_location {

  public:
#if defined __clang__ && __clang_major__ >= 9 || defined _MSC_VER && _MSC_VER >= 1920
    static constexpr source_location current( std::string_view fileName = __builtin_FILE(),
                                              std::string_view functionName = __builtin_FUNCTION(),
                                              const uint_least32_t lineNumber = __builtin_LINE(),
                                              const uint_least32_t columnOffset = __builtin_COLUMN() ) noexcept
#else
  #if defined __GNUC__ && ( __GNUC__ > 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ >= 8 ) )
    static constexpr source_location current( const char *fileName = __builtin_FILE(),
                                              const char *functionName = __builtin_FUNCTION(),
                                              const uint_least32_t lineNumber = __builtin_LINE(),
                                              const uint_least32_t columnOffset = 0 ) noexcept
  #else
    static constexpr source_location current( const char *fileName = "unsupported",
                                              const char *functionName = "unsupported",
                                              const uint_least32_t lineNumber = 0,
                                              const uint_least32_t columnOffset = 0 ) noexcept
  #endif
#endif
    {
      return { fileName, functionName, lineNumber, columnOffset };
    }

    source_location( const source_location & ) = default;
    source_location( source_location && ) = default;

    [[nodiscard]] constexpr std::string_view file_name() const noexcept {

      return fileName;
    }

    [[nodiscard]] constexpr std::string_view function_name() const noexcept {

      return functionName;
    }

    [[nodiscard]] constexpr uint_least32_t line() const noexcept {

      return lineNumber;
    }

    [[nodiscard]] constexpr std::uint_least32_t column() const noexcept {

      return columnOffset;
    }

  private:
    constexpr source_location( std::string_view _fileName,
                               std::string_view _functionName,
                               const uint_least32_t _lineNumber,
                               const uint_least32_t _columnOffset ) noexcept
      : fileName( _fileName ),
        functionName( _functionName ),
        lineNumber( _lineNumber ),
        columnOffset( _columnOffset ) {}

    std::string_view fileName;
    std::string_view functionName;
    const std::uint_least32_t lineNumber;
    const std::uint_least32_t columnOffset;
  };
}
