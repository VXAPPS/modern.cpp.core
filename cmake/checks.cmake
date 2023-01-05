#
# Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

include(CheckCXXSourceCompiles)
include(CheckIncludeFileCXX)

check_include_file_cxx(format HAVE_FORMAT_INCLUDE)
if(HAVE_FORMAT_INCLUDE)
  check_cxx_source_compiles(
    "#include <cstdint>
    #include <format>
    #include <string>
    #include <tuple>
    std::int32_t main() { std::ignore = std::format( \"The answer is {}.\", 42 ); return 0; }"
    HAVE_FORMAT
  )
endif()

check_include_file_cxx(thread HAVE_THREAD_INCLUDE)
if(HAVE_THREAD_INCLUDE)
  check_cxx_source_compiles(
    "#include <cstdint>
    #include <thread>
    #include <tuple>
    std::int32_t main() { std::ignore = std::jthread::hardware_concurrency(); return 0; }"
    HAVE_JTHREAD
  )
endif()

check_include_file_cxx(ranges HAVE_RANGES_INCLUDE)
if(HAVE_RANGES_INCLUDE)
  check_cxx_source_compiles(
    "#include <algorithm>
    #include <array>
    #include <cstdint>
    #include <ranges>
    std::int32_t main() { std::array list = { 1, 4, 2, 3 }; std::ranges::sort( list ); (void)list; return 0; }"
    HAVE_RANGES
  )
endif()

check_include_file_cxx(source_location HAVE_SOURCE_LOCATION_INCLUDE)
if(HAVE_SOURCE_LOCATION_INCLUDE)
  check_cxx_source_compiles(
    "#include <cstdint>
    #include <source_location>
    #include <tuple>
    std::int32_t main() { std::ignore = std::source_location::current(); return 0; }"
    HAVE_SOURCE_LOCATION
  )
endif()

check_include_file_cxx(span HAVE_SPAN_INCLUDE)
if(HAVE_SPAN_INCLUDE)
  check_cxx_source_compiles(
    "#include <cstdint>
    #include <span>
    std::int32_t main( std::int32_t argc, char **argv ) { std::span args( argv, static_cast<std::size_t>( argc ) ); (void)args; return 0; }"
    HAVE_SPAN
  )
endif()
