/*
 * Copyright (c) 2023 Florian Becker <fb@vxapps.com> (VX APPS).
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
#include <cstdio> // std::remove

/* gtest header */
#include <gtest/gtest.h>

/* modern.cpp.core */
#include <CSVWriter.h>

using ::testing::InitGoogleTest;
using ::testing::Test;

#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace vx {

  TEST( CSV, Simple ) {

    using namespace std::literals;

    const std::vector data = { "Hans"sv, "1.23"sv, "Manchester"sv };
    const CSVWriter writer( "test.csv" );
    writer.addRowData( std::cbegin( data ), std::cend( data ) );

    std::vector<char> dump {};
    std::ifstream input( "test.csv", std::ios::in | std::ios::binary );
    if ( !input.is_open() ) {

      std::cout << "Cannot open file for import." << std::endl;
    }
    if ( !input.eof() && !input.fail() ) {

      input.seekg( 0, std::ios_base::end );
      const std::streampos size = input.tellg();
      dump.resize( static_cast<std::size_t>( size ) );

      input.seekg( 0, std::ios_base::beg );
      input.read( dump.data(), size );
    }
    try {

      input.close();
    }
    catch ( const std::ofstream::failure &_exception ) {

      std::cout << _exception.what() << std::endl;
    }
    std::remove( "test.csv" );

    std::string converted( std::cbegin( dump ), std::cend( dump ) );
#ifdef _WIN32
    EXPECT_EQ( converted, "Hans,1.23,Manchester\r\n" );
#else
    EXPECT_EQ( converted, "Hans,1.23,Manchester\n" );
#endif
  }
}
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

std::int32_t main( std::int32_t argc,
                   char **argv ) {

  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
