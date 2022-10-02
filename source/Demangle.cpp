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
#ifndef _WIN32
  #include <cxxabi.h>
#endif

/* stl header */
#include <regex>

/* local header */
#include "Demangle.h"
#include "StringUtils.h"

namespace vx {

  std::string demangle( const std::string &_name ) noexcept {

    std::string result = _name;

#ifndef _WIN32
    /**
     *  0: The demangling operation succeeded.
     * -1: A memory allocation failiure occurred.
     * -2: mangled_name is not a valid name under the C++ ABI mangling rules.
     * -3: One of the arguments is invalid.
     * */
    int status = -4;

    const std::unique_ptr<char, void ( * )( void * )> res {

      abi::__cxa_demangle( _name.c_str(), nullptr, nullptr, &status ),
      std::free
    };

    if ( status == 0 ) {

      result = res.get();
    }
#endif

    // WINDOWS
    result = std::regex_replace( result, std::regex( "class" ), "" );
    result = std::regex_replace( result, std::regex( "struct" ), "" );
    result = std::regex_replace( result, std::regex( "__ptr64" ), "" );
    //    result = std::regex_replace( result, std::regex( "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" ), "std::string" );
    //    result = std::regex_replace( result, std::regex( "class std::basic_string_view<char,struct std::char_traits<char> >" ), "std::string" );

    // LINUX clang and gcc
    result = std::regex_replace( result, std::regex( "__cxx11::" ), "" );
    //    result = std::regex_replace( result, std::regex( "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >" ), "std::string" );
    //    result = std::regex_replace( result, std::regex( "std::basic_string_view<char, std::char_traits<char> >" ), "std::string_view" );

    // MAC AppleClang
    result = std::regex_replace( result, std::regex( "__1::" ), "" );
    //    result = std::regex_replace( result, std::regex( "std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >" ), "std::string" );
    //    result = std::regex_replace( result, std::regex( "std::__1::basic_string_view<char, std::__1::char_traits<char> >" ), "std::string_view" );

    // All, after general cleanup
    result = std::regex_replace( result, std::regex( "std::basic_string<char, std::char_traits<char>, std::allocator<char> >" ), "std::string" );
    result = std::regex_replace( result, std::regex( "std::basic_string_view<char, std::char_traits<char> >" ), "std::string_view" );

    // Remove space before closing bracket - overall valid
    result = std::regex_replace( result, std::regex( ", >" ), ">" );
    result = std::regex_replace( result, std::regex( ",>" ), ">" );
    result = std::regex_replace( result, std::regex( " >" ), ">" );
    result = string_utils::simplified( result );

    return result;
  }

  std::string demangleExtreme( const std::string &_name ) noexcept {

    std::string result = demangle( _name );

    /* Everything to cut out until end to simplify the types printed */
    const std::vector toRemove { "std::less", "std::hash", "std::equal_to", "std::allocator" };
    for ( const auto &remove : toRemove ) {

      const std::size_t pos = result.find( remove );
      if ( pos != std::string::npos ) {

        result = result.replace( pos, result.size() - 1 - pos, "" );
      }
    }

    /* reorder for const type pointer/reference */
    result = std::regex_replace( result, std::regex( "int const" ), "const int " );
    result = std::regex_replace( result, std::regex( "double const" ), "const double " );
    result = std::regex_replace( result, std::regex( "char const" ), "const char " );

    /* Remove space before closing bracket - overall valid */
    result = std::regex_replace( result, std::regex( ", >" ), ">" );
    result = std::regex_replace( result, std::regex( ",>" ), ">" );
    result = std::regex_replace( result, std::regex( " >" ), ">" );
    result = string_utils::simplified( result );

    /* Try to fix no spaces and comma issues */
    result = std::regex_replace( result, std::regex( " ," ), "," );
    if ( result.find( ", " ) == std::string::npos ) {

      result = std::regex_replace( result, std::regex( "," ), ", " );
    }

    return result;
  }
}
