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

/* c header */
#include <cstdint> // std::int32_t
#include <cstdlib> // std::free
#ifndef _WIN32
  #include <cxxabi.h>
#endif

/* stl header */
#include <exception>
#include <memory>
#include <new> // std::bad_alloc
#include <string>
#include <string_view>
#include <vector>

/* re2 header */
#include <re2/re2.h>

/* local header */
#include "Demangle.h"
#include "Logger.h"
#include "StringUtils.h"

namespace vx::demangle {

  std::string abi( const std::string &_name ) {

    std::string result = _name;

#ifndef _WIN32
    /**
     *  0: The demangling operation succeeded.
     * -1: A memory allocation failure occurred.
     * -2: mangled_name is not a valid name under the C++ ABI mangling rules.
     * -3: One of the arguments is invalid.
     * */
    std::int32_t status = -4;

    const std::unique_ptr<char, void ( * )( char * )> res {

      abi::__cxa_demangle( _name.c_str(), nullptr, nullptr, &status ),
      []( char *_toFree ) { std::free( _toFree ); } // NOSONAR raii is not possible here.
    };

    if ( status == 0 ) {

      result = res.get();
    }
#endif

    return result;
  }

  std::string simple( const std::string &_name ) {

    std::string result = abi( _name );

    // WINDOWS
    RE2::GlobalReplace( &result, "class", "" );
    RE2::GlobalReplace( &result, "struct", "" );
    RE2::GlobalReplace( &result, "__ptr64", "" );

    RE2::GlobalReplace( &result, "enum `private: virtual void __cdecl ", "" );
    RE2::GlobalReplace( &result, " '::`2'", "" );
    RE2::GlobalReplace( &result, "(void)", "" );

    // LINUX clang and gcc
    RE2::GlobalReplace( &result, "__cxx11::", "" );

    // MAC AppleClang
    RE2::GlobalReplace( &result, "__1::", "" );

    // All, after general cleanup
    RE2::GlobalReplace( &result, "std::basic_string<char, std::char_traits<char>, std::allocator<char> >", "std::string" );
    RE2::GlobalReplace( &result, "std::basic_string<char, std::char_traits<char>, std::allocator<char>>", "std::string" );
    RE2::GlobalReplace( &result, "std::basic_string_view<char, std::char_traits<char> >", "std::string_view" );
    RE2::GlobalReplace( &result, "std::basic_string_view<char, std::char_traits<char>>", "std::string_view" );

    /* Remove space after opening bracket - overall valid */
    RE2::GlobalReplace( &result, "< ", "<" );

    // Remove space before closing bracket - overall valid
    RE2::GlobalReplace( &result, ", >", ">" );
    RE2::GlobalReplace( &result, ",>", ">" );
    RE2::GlobalReplace( &result, " >", ">" );
    result = string_utils::simplified( result );

    return result;
  }

  std::string extreme( const std::string &_name ) {

    using namespace std::literals;

    std::string result = simple( _name );

    try {

      /* Everything to cut out until end to simplify the types printed */
      for ( const std::vector toRemove { "std::less"sv, "std::hash"sv, "std::equal_to"sv, "std::allocator"sv }; const auto &remove : toRemove ) {

        const std::size_t pos = result.find( remove );
        if ( pos != std::string::npos ) {

          result = result.replace( pos, result.size() - 1 - pos, "" );
        }
      }
    }
    catch ( const std::bad_alloc &_exception ) {

      logFatal() << "bad_alloc:" << _exception.what();
    }
    catch ( const std::exception &_exception ) { // NOSONAR fallback for every exeption.

      logFatal() << _exception.what();
    }

    /* reorder for const type pointer/reference */
    RE2::GlobalReplace( &result, "int const", "const int " );
    RE2::GlobalReplace( &result, "double const", "const double " );
    RE2::GlobalReplace( &result, "char const", "const char " );

    /* Remove space after opening bracket - overall valid */
    RE2::GlobalReplace( &result, "< ", "<" );

    /* Remove space before closing bracket - overall valid */
    RE2::GlobalReplace( &result, ", >", ">" );
    RE2::GlobalReplace( &result, ",>", ">" );
    RE2::GlobalReplace( &result, " >", ">" );
    result = string_utils::simplified( result );

    /* Try to fix no spaces and comma issues */
    RE2::GlobalReplace( &result, " ,", "," );
    if ( result.find( ", " ) == std::string::npos ) {

      RE2::GlobalReplace( &result, ",", ", " );
    }

    return result;
  }
}
